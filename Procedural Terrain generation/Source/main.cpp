#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include "UI.h"
#include "Shader.h"
#include "Camera.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

float heightScale = 10.0f;
Camera cam;

// Light Values
glm::vec3 lightDirection(-6.0f, 3.5f, -1.0f);
glm::vec3 lightColor(2.0f, 2.0f, 2.0f);

const int WIDTH = 1440;
const int HEIGHT = 1080;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Millie", NULL, NULL);
	if (window == nullptr)
	{
		Log("Failed to load Window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	bool showWindow = true;

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shadowShader("../Shaders/Shadow.vs", "../Shaders/Shadow.fs");
	Shader erosionShader("../Shaders/Erosion.comp");
	Shader terrainShader("../Shaders/Terrain.vs", "../Shaders/Terrain.fs", "", "../Shaders/Terrain.tcs", "../Shaders/Terrain.tes");
	Shader SkyboxShader("../Shaders/Skybox.vs", "../Shaders/Skybox.fs");

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100000.0f);
		glm::mat4 view = cam.GetView();
		terrainShader.SetMatrix4("projection", projection);
		terrainShader.SetMatrix4("view", view);

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		terrainShader.SetMatrix4("model", model);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


void ProcessInput(GLFWwindow* window)
{
	cam.ProcessInput(window);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	cam.ProcessOffset(xpos, ypos);
}

void DrawSkyBox()
{

}

void ShadowPass()
{

}

void DrawTerrain()
{

}
