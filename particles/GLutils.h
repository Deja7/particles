#pragma once
#include "includes.h"

void initGL() {
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//stbi_set_flip_vertically_on_load(true);
}

/*
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) return;
	if (!mouse.isInit) {
		mouse.lastX = xpos;
		mouse.lastY = ypos;
		mouse.isInit = true;
	}
	float sensitivity = 0.5f;
	mouse.offsetX = (xpos - mouse.lastX) * sensitivity;
	mouse.offsetY = (mouse.lastY - ypos) * sensitivity;

	mouse.lastX = xpos;
	mouse.lastY = ypos;
}
*/

/*
void processInput(GLFWwindow* window, Camera& camera, float delta) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float cameraSpeed = 15.f * delta;

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) cameraSpeed = 100.f * delta;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.pos += cameraSpeed * camera.front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.pos -= cameraSpeed * camera.front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.pos -= glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.pos += glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.pos += cameraSpeed * camera.up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.pos -= cameraSpeed * camera.up;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
*/

/*
void processInput(GLFWwindow* window, Camera& camera, Car& car) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float speed = 30.f;
	float TURN = glm::radians(30.f);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) speed = 50.f;
	car.thrust = 0.f;
	car.turn = 0.f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) car.thrust = speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) car.thrust = -speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		car.turn = TURN;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		car.turn = -TURN;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		car.isDrift = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		car.isDrift = 0;
	}
	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	//    camera.pos += cameraSpeed * camera.up;
	//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//    camera.pos -= cameraSpeed * camera.up;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
*/

class GLHandler {
public:
	float width = 800.f;
	float height = 800.f;
	GLFWwindow* win;
	void start() {
		win = glfwCreateWindow(width, height, "Particles", NULL, NULL);
		if (win == NULL) {
			std::cout << "Failed to create a window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(win);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
		glViewport(0, 0, width, height);
		//glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
		//glfwSetCursorPosCallback(win, mouse_callback);
		//glfwSetMouseButtonCallback(winwindow, mouse_button_callback);
		//glfwSetKeyCallback(win, key_callback);
		//glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//glEnable(GL_MULTISAMPLE);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_POINT_SIZE);
		//glPointSize(10.f);
		glLineWidth(10.f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void display() {
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	void clear() {
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void initImGui() {
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//ImGui::StyleColorsDark();
		//ImGui_ImplGlfw_InitForOpenGL(win, true);
		//ImGui_ImplOpenGL3_Init("#version 450");
	}
};

