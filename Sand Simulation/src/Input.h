#pragma once

//#include <GLFW/glfw3.h>
//#include "Window.h"
#include "glm/glm.hpp"

#include <map>
#include <vector>

namespace Input {

    extern glm::vec2 mousePosition;
    extern glm::vec2 normalizedMousePosition;
    extern glm::vec2 worldMousePosition;
    extern glm::vec2 mouseScroll;

    //void SetupKeyInputs(GLFWwindow* window);

    //void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    //void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    //void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    //void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    //bool IsKeyPressed(int key);
    //void SetKeyDown(int key, bool isDown);
}