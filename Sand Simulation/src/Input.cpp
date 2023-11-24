#include "Input.h"

#include <iostream>

namespace Input {
	glm::vec2 mousePosition = { 0.0f, 0.0f };
	glm::vec2 normalizedMousePosition = { 0.0f, 0.0f };
	glm::vec2 worldMousePosition = { 0.0f, 0.0f };

	glm::vec2 aspectRatio = {16, 9};

	glm::vec2 mouseScroll = { 0.0f, 0.0f };

	std::map<int, bool> m_Keys;
	std::vector<int> m_KeysToMonitor = {
		GLFW_KEY_W,
		GLFW_KEY_S,
		GLFW_KEY_A,
		GLFW_KEY_D,

		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
		GLFW_KEY_0,

		GLFW_KEY_SPACE,
		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_LEFT_ALT,

		GLFW_KEY_ESCAPE,
		GLFW_KEY_TAB,

		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_RIGHT,
		GLFW_MOUSE_BUTTON_MIDDLE,

		GLFW_MOUSE_BUTTON_4,
		GLFW_MOUSE_BUTTON_5,
		GLFW_MOUSE_BUTTON_6,
	};

	void SetupKeyInputs(GLFWwindow* window)
	{
		for (int key : m_KeysToMonitor)
		{
			m_Keys[key] = false;
		}

		glfwSetKeyCallback(window, KeyCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetCursorPosCallback(window, MousePositionCallback);
		glfwSetScrollCallback(window, MouseScrollCallback);
	}
	
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		SetKeyDown(key, action != GLFW_RELEASE);
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		SetKeyDown(button, action != GLFW_RELEASE);
	}

	glm::vec2 ScreenToWorldSpace(glm::vec2 screenPos, glm::vec2 cameraPos, glm::vec2 cameraSize)
	{
		return cameraPos + (screenPos / cameraSize);
	}





	glm::vec3 ScreenToClipSpace(glm::vec2 screenPos, glm::vec2 screenSize)
	{
		float x = (screenPos.x / screenSize.x) * 2.0f - 1.0f;
		float y = (screenPos.y / screenSize.y) * 2.0f - 1.0f;
		return glm::vec3(x, y, 0.0f);
	}

	glm::vec4 ClipToWorldSpace(glm::vec4 clipPos, glm::mat4 invMVP)
	{
		glm::vec4 worldPos = invMVP * clipPos;
		return worldPos;// / worldPos.w;
	}

	void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		aspectRatio = { (float)width, (float)height };

		mousePosition.x = (float)xpos;
		mousePosition.y = height - (float)ypos;

		// Normalized in screen space
		//normalizedMousePosition.x = (float)xpos / (float)width;
		//normalizedMousePosition.y = (height - (float)ypos) / (float)height;

		// Normalized in chunk space
		//normalizedMousePosition.x = (float)xpos / (5.0f * (64 * 4));
		//normalizedMousePosition.y = (height - (float)ypos) / (3.0f * (64 * 4));

		//glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

		//glm::mat4 VP = proj * view;
		//glm::mat4 invMVP = glm::inverse(VP);

		//glm::vec3 clipSpace = ScreenToClipSpace(mousePosition, {(float)width, (float)height});
		////std::cout << clipSpace.x << ", " << clipSpace.y << std::endl;

		//glm::vec4 clipPos = glm::vec4(clipSpace.x, clipSpace.y, 0, 1.0f);
		//glm::vec4 worldPos = ClipToWorldSpace(glm::vec4(clipPos), invMVP);
		////std::cout << worldPos.x << ", " << worldPos.y << std::endl;

		//worldMousePosition.x = worldPos.x;
		//worldMousePosition.y = worldPos.y;
	}

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouseScroll.x = (float)xoffset;
		mouseScroll.y = (float)yoffset;
	}

	bool IsKeyPressed(int key)
	{
		bool result = false;

		std::map<int, bool>::iterator it = m_Keys.find(key);
		if (it != m_Keys.end()) {
			result = it->second;
		}

		return result;
	}

	void SetKeyDown(int key, bool isDown)
	{
		std::map<int, bool>::iterator it = m_Keys.find(key);
		if (it != m_Keys.end()) {
			it->second = isDown;
		}
	}
}