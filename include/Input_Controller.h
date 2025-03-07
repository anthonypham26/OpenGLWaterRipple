#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Input_Controller
{
public:
    Input_Controller() = default;

    // --- Static Callbacks: GLFW requires these be static ---
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // --- Non-static handlers that do the real work ---
    void handleMouseButton(int button, int action, int mods);

    // --- Accessors for retrieving click data in main.cpp ---
    float getLastClickTime() const;
    glm::vec2 getLastClickPos() const;

private:
    float   m_lastClickTime;   // Time of the last mouse click
    glm::vec2 m_lastClickPos;  // Normalized position of the last click (-1..1 range)
};

#endif


// #include <glm/glm.hpp>          // For glm::vec2
// #include <GLFW/glfw3.h>         // For GLFW functions
// #include <algorithm>            // For std::clamp

// class Input_Controller
// {
// private:
//     glm::vec2 m_offset;     // The accumulated offset (pan offset)
//     glm::vec2 m_lastMouse;  // The last mouse position
//     float m_panSpeed;       // The speed at which panning occurs
//     bool m_firstMouse;      // Flag to check if this is the first mouse event

// public:
//     // Constructor with default pan speed
//     Input_Controller(float panSpeed = 0.005f)
//         : m_offset(0.0f),
//           m_lastMouse(0.0f),
//           m_panSpeed(panSpeed),
//           m_firstMouse(true)
//     {
//     }

//     // Static callback passed to GLFW for mouse movement
//     static void mouseCallback(GLFWwindow* window, double xPos, double yPos)
//     {
//         // Retrieve our Input_Controller from the window user pointer
//         Input_Controller* controller = static_cast<Input_Controller*>(glfwGetWindowUserPointer(window));
//         if (controller)
//         {
//             // Pass the mouse coordinates to the handling function
//             controller->handleMouseInput(xPos, yPos);
//         }
//     }

//     // Function that processes mouse input for panning
//     void handleMouseInput(double xPos, double yPos)
//     {
//         // Get current window size for normalization
//         int width, height;
//         glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

//         // Convert positions to floats
//         glm::vec2 currentPosition(static_cast<float>(xPos), static_cast<float>(yPos));

//         // On the very first mouse move, initialize m_lastMouse
//         if (m_firstMouse)
//         {
//             m_lastMouse = currentPosition;
//             m_firstMouse = false;
//         }

//         // Calculate the mouse movement delta
//         glm::vec2 delta = currentPosition - m_lastMouse;

//         // Normalize the delta by window size; invert Y so that
//         // moving the mouse up gives positive offset
//         glm::vec2 normalizedDelta(delta.x / static_cast<float>(width),
//                                   -delta.y / static_cast<float>(height));

//         // Accumulate the offset (apply pan speed)
//         m_offset += normalizedDelta * m_panSpeed;

//         // Clamp offset to a [-1, 1] range in both X and Y
//         m_offset.x = std::clamp(m_offset.x, -1.0f, 1.0f);
//         m_offset.y = std::clamp(m_offset.y, -1.0f, 1.0f);

//         // Update the last mouse position for the next event
//         m_lastMouse = currentPosition;
//     }

//     // Example getter to retrieve the offset from outside this class
//     glm::vec2 getOffset() const { return m_offset; }
// };
