#include "includes.h"
#include "GLutils.h"
#include "shader.h"
GLHandler GLH;

struct particle {
	glm::vec4 pos;
	glm::vec4 vel;
};

int main() {
	srand(time(nullptr));
	initGL();
	GLH.start();

	//particles init
	const int PARTICLE_COUNT = 100000;
	particle* particles = new particle[PARTICLE_COUNT];
	for (int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i].pos.x = float(rand() % 2001 - 1000) / 1000.f;
		particles[i].pos.y = float(rand() % 2001 - 1000) / 1000.f;
		particles[i].pos.z = float(rand() % 2001 - 1000) / 1000.f;
		//particles[i].pos = glm::vec4(0.1);

		float l = sqrtf(particles[i].pos.x * particles[i].pos.x + particles[i].pos.y * particles[i].pos.y + particles[i].pos.z * particles[i].pos.z);
		l *= (1 + (float(rand() % 3000) / 10000.f));
		particles[i].pos /= l;
		particles[i].pos.w = 1.0;
		//particles[i].vel = glm::vec4(0.f);
		particles[i].vel.x = float(rand() % 2001 - 1000) / 10000.f;
		particles[i].vel.y = float(rand() % 2001 - 1000) / 10000.f;
		particles[i].vel.z = float(rand() % 2001 - 1000) / 10000.f;
		particles[i].vel.w = 0;
		//printf("%f %f %f\n", tmp.pos.x, tmp.pos.y, tmp.pos.z);
	}

	//Shader compute()
	ComputeShader compute("compute.glsl");
	Shader shader("vertex.glsl", "fragment.glsl");

	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(particle) * PARTICLE_COUNT, particles, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	float prevTime = glfwGetTime();
	while (true) {
		float currentTime = glfwGetTime();
		float delta = currentTime - prevTime;
		GLH.clear();
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();
		//ImGui::Begin("Debug");


		compute.use();
		compute.setFloat("dt", delta / 1); // deltaTime
		glDispatchCompute((PARTICLE_COUNT + 255) / 256, 1, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(80.f), GLH.width / GLH.height, 0.1f, 100000.f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 transform = projection * view;

		shader.use();
		shader.setMat4("transform", transform);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
		glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);



		//ImGui::Checkbox("Draw Triangle", &drawTriangle);
		//ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		//ImGui::ColorEdit4("Color", color);
		// 
		//ImGui::End();
		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLH.display();
		//processInput(GLH.win, camera, delta);
		//processInput(GLH.win, camera, car);
		//camera.rotate(mouse);
		prevTime = currentTime;
	}
	
	return 0;
}