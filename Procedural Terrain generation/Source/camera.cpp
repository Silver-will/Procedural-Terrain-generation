#include<glm/gtc/type_ptr.hpp>
#include "Camera.h"
Camera::Camera()
{
	upValue = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraPos = glm::vec3(0.0f, 20.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	Right = glm::normalize(cross(cameraTarget, upValue));
	view = glm::lookAt(cameraPos, cameraTarget, upValue);
	zoom = 45.0f;
}

void Camera::ProcessInput(GLFWwindow* window,int action, int key)
{
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_C && cursor_locked)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cursor_locked = false;
		}
		else if (key == GLFW_KEY_C)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			cursor_locked = true;
			fMouse = true;
		}
	}
}

void Camera::ProcessOffset(GLfloat xPos, GLfloat yPos)
{
	if (cursor_locked)
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
			yOffset = lastY - yPos;
			lastX = xPos;
			lastY = yPos;
		}

		xOffset *= sensitivity;
		yOffset *= sensitivity;

		yaw += xOffset;
		pitch += yOffset;

		//clamp the values to prevent weird snapping
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		cameraTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraTarget.y = sin(glm::radians(pitch));
		cameraTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		SetTarget(normalize(cameraTarget));
	}
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

void Camera::MoveCamera(GLFWwindow* window)
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