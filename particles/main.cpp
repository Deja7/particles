#include "includes.h"
#include "GLutils.h"
GLHandler GLH;
int main() {
	initGL();
	GLH.start();


	float prevTime = glfwGetTime();
	while (true) {

		float currentTime = glfwGetTime();
		float delta = currentTime - prevTime;
		GLH.clear();
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();
		//ImGui::Begin("Debug");





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