#include<glm/gtc/type_ptr.hpp>
#include "Camera.h"
Camera::Camera()
{
	upValue = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	Right = glm::normalize(cross(cameraTarget, upValue));
	view = glm::lookAt(cameraPos, cameraTarget, upValue);
	zoom = 45.0f;
}

void Camera::ProcessInput(GLFWwindow* window)
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	GLfloat speed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))
	{
		cameraPos -= speed * Right;
	}
	if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		cameraPos += speed * Right;
	}
	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP))
	{
		cameraPos += cameraTarget * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))
	{
		cameraPos -= cameraTarget * speed;
	}
}

void Camera::ProcessOffset(GLfloat xPos, GLfloat yPos)
{
	if (fMouse)
	{
		fMouse = false;
		lastX = xPos;
		lastY = yPos;
	}
	else
	{
		xOffset = xPos - lastX;
		yOffset = yPos - lastY;
		lastX = xPos;
		lastY = yPos;
	}

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	cameraTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraTarget.y = sin(glm::radians(pitch));
	cameraTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	SetTarget(normalize(cameraTarget));
}

void Camera::UpdateCameraVector()
{
	this->view = glm::lookAt(cameraPos, cameraPos + cameraTarget, upValue);
	this->Right = glm::normalize(glm::cross(cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->upValue = glm::normalize(glm::cross(Right, cameraTarget));
}

void Camera::SetTarget(glm::vec3 direction)
{
	this->cameraTarget = direction;
	UpdateCameraVector();
}
glm::mat4 Camera::GetView()
{
	UpdateCameraVector();
	return this->view;
}

glm::vec3 Camera::GetPos()
{
	return this->cameraPos;
}

glm::vec3 Camera::GetTarget()
{
	return this->cameraTarget;
}

glm::vec3 Camera::GetDir()
{
	return this->cameraTarget;
}
