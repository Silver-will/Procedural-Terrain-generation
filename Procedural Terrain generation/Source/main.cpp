#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include "UI.h"
#include "Shader.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
void PouseCallback(GLFWwindow* window, double xpos, double ypos);
void PcrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

float heightScale = 10.0f;

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
	//glfwSetMouseButtonCallback(window, MouseButtonCallback);

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

	}
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}