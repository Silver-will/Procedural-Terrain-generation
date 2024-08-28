#include<iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "UI.h"
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"
#include "Texture.h"
#include "Math.h"
#include "Buffer.h"

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
	glfwWindowHint(GLFW_SAMPLES, 4);

	

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Terr 3D", NULL, NULL);
	if (window == nullptr)
	{
		Log("Failed to load Window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	bool showWindow = true;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	//Load Shaders
	//Shader shadowShader("/Shaders/Shadow.vs", "/Shaders/Shadow.fs", "", "/Shaders/Shadow.tcs", "/Shaders/Shadow.tes");
	//Shader erosionShader("../Shaders/Erosion.comp");
	Shader terrainShader("/Shaders/Terrain.vs", "/Shaders/Terrain.fs", "", "/Shaders/Terrain.tcs", "/Shaders/Terrain.tes");
	//Shader SkyboxShader("/Shaders/Skybox.vs", "/Shaders/Skybox.fs");

	//Load Terrain Textures
	Texture meadowDiffuse("/Resources/meadowDiffuse.png", GL_REPEAT, GL_LINEAR);
	Texture meadowHeight("/Resources/meadowHeight.png", GL_REPEAT, GL_LINEAR);
	Texture meadowNormal("/Resources/meadowNormal.png", GL_REPEAT, GL_LINEAR);

	Texture sandDiffuse("/Resources/sandDiffuse.png", GL_REPEAT, GL_LINEAR);
	Texture sandHeight("/Resources/sandHeight.png", GL_REPEAT, GL_LINEAR);
	Texture sandNormal("/Resources/sandNormal.png", GL_REPEAT, GL_LINEAR);

	Terrain terr(256, 256);
	terr.GenerateVertices();

	terrainShader.use();
	terrainShader.SetInteger("meadowDiffuse", meadowDiffuse.index);
	terrainShader.SetInteger("meadowHeight", meadowHeight.index);
	terrainShader.SetInteger("meadowNormal", meadowNormal.index);
	terrainShader.SetInteger("sandDiffuse", sandDiffuse.index);
	terrainShader.SetInteger("sandHeight", sandHeight.index);
	terrainShader.SetInteger("sandNormal", sandNormal.index);
	terrainShader.SetInteger("noiseMap", terr.map.noisetexture.index);

	GLuint terrainId = glGetUniformBlockIndex(terrainShader.shad, "Matrices");
	//GLuint shadowId = glGetUniformBlockIndex(shadowShader.shad, "Matrices");
	glUniformBlockBinding(terrainShader.shad, terrainId, 0);
	//glUniformBlockBinding(shadowShader.shad, shadowId, 0);

	UniformData data;
	data.proj = glm::perspective(cam.zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	GLuint ubo{};
	CreateUniformBuffer(ubo,sizeof(UniformData));
	UploadToUniformBuffer(ubo, 0, data.proj);

	glm::vec3 lightDir;
	lightDir = glm::vec3(-1, 0, 0);
	std::cout << sandNormal.index << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		data.model = glm::mat4(1.0f);
		UploadToUniformBuffer(ubo, sizeof(glm::mat4), data.model);

		data.view = cam.GetView();
		UploadToUniformBuffer(ubo, sizeof(glm::mat4) * 2, data.view);

		data.mvp = data.proj * data.view * data.model;
		UploadToUniformBuffer(ubo, sizeof(glm::mat4) * 3, data.mvp);

		//Bind Textures
		terrainShader.use();
		meadowDiffuse.BindTexture();
		meadowHeight.BindTexture();
		meadowNormal.BindTexture();
		sandDiffuse.BindTexture();
		sandHeight.BindTexture();
		sandNormal.BindTexture();
		terr.BindFBM();
		//Draw Terrain
		terr.Draw();

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
