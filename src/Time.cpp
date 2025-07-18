#include "Time.h"
#include <GLFW/glfw3.h>

namespace Time {
    double lastTime = glfwGetTime();
    double currentTime = 0;
    double deltaTime = 0;

    void Update() {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    }
}