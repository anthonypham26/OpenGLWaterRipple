#include "Input_Controller.h"
#include <iostream>     // For debugging/printing
#include <algorithm>    // For std::clamp 


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
        
        
        // Texture Coordinates
        float texX = 200.0f;  
        float texY = 150.0f;    
        float texWidth = 400.0f;
        float texHeight = 300.0f;

        // Read the mouse position in window coordinates
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        std::cout << "X: " << mouseX << " Y: " << mouseY << std::endl;


        // Compute texture-relative normalized coordinates:
        float normalizedTexX = (static_cast<float>(mouseX) - texX) / texWidth;
        float normalizedTexY = ( 1 - (static_cast<float>(mouseY) - texY) / texHeight);
        
        // std::cout << "normX: " << normalizedTexX << " normY: " << normalizedTexY << std::endl;

        m_lastClickPos = glm::vec2(normalizedTexX, normalizedTexY);
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
