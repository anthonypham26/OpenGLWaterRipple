#include "Input_Controller.h"
#include <iostream>     // For debugging/printing if needed
#include <algorithm>    // For std::clamp (if you use it)


// ---------------------------------------------------------
// Static: Mouse Button Callback
// ---------------------------------------------------------
void Input_Controller::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // Retrieve our instance of Input_Controller from the window user pointer
    Input_Controller* controller = static_cast<Input_Controller*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->handleMouseButton(button, action, mods);
    }
}

// ---------------------------------------------------------
// Non-static: Actually handle mouse button events
// ---------------------------------------------------------
void Input_Controller::handleMouseButton(int button, int action, int /*mods*/)
{
    // When left button is pressed, record time & position
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // Store the time of the click
        m_lastClickTime = static_cast<float>(glfwGetTime());

        // Get window size to normalize the click position
        GLFWwindow* window = glfwGetCurrentContext();
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Read the mouse position in window coordinates
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Convert [0..width], [0..height] => [-1..1], [-1..1]
        float normalizedX = static_cast<float>(mouseX) / static_cast<float>(width)  * 2.0f - 1.0f;
        float normalizedY = 1.0f - (static_cast<float>(mouseY) / static_cast<float>(height));
        normalizedY = normalizedY * 2.0f - 1.0f;

        // Store click position
        m_lastClickPos = glm::vec2(normalizedX, normalizedY);
    }
}

// ---------------------------------------------------------
// Accessors
// ---------------------------------------------------------
float Input_Controller::getLastClickTime() const
{
    return m_lastClickTime;
}

glm::vec2 Input_Controller::getLastClickPos() const
{
    return m_lastClickPos;
}
