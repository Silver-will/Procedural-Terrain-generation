#ifndef CAMERA_H
#define CAMERA_H
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
struct Camera
{
	Camera();
	void ProcessInput(GLFWwindow* window, int action, int key);
	void ProcessOffset(GLfloat xPos, GLfloat yPos);
	void MoveCamera(GLFWwindow* window);
	void SetTarget(glm::vec3 direction);
	void UpdateCameraVector();
	glm::mat4 GetView();
	glm::vec3 GetPos();
	glm::vec3 GetTarget();
	glm::vec3 GetDir();
	GLfloat zoom;

private:
	glm::vec3 upValue;
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::mat4 view;
	glm::vec3 Right;


	//Camera Values
	GLfloat deltaTime{};
	GLfloat lastFrame{};
	GLfloat currentFrame{};
	GLfloat cameraNearPlane{ 0.1f };
	GLfloat cameraFarPlane{ 500.0f };
	GLfloat yaw = -90.0f, pitch = 0.0f, sensitivity = 0.1f, lastX{}, lastY{}, xOffset{}, yOffset{};
	bool fMouse = true;
	bool cursor_locked = true;
};
#endif