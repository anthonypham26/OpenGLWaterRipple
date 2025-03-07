#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "shaderClass.h"
#include "Texture.h"

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#include <iostream>
#include <glm/glm.hpp>
#include <Input_Controller.h>

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	-1.0f, -1.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	-1.0f,  1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	 1.0f,  1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 	 1.0f, -1.0f  // Lower right corner//
	//-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	//-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	// 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	// 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main()
{
	try 
	{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Automatic Animation", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); // Introduce the window into the current context
	gladLoadGL(); //Load GLAD so it configures OpenGL
	glViewport(0, 0, 1000, 1000); // Specify the viewport of OpenGL in the Window

	// Generates Shader object using shaders default.vert and default.frag
	shaderClass shaderProgram("../shaders/default.vert", "../shaders/default.frag");
	if (shaderProgram.ID == 0) {
		std::cout << "Failed to initialize shader program" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Image Handling
	std::string texPath = "../include/texture/AnthonyMackie.png";
	Texture myPhoto((texPath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); // loads the image file, creates an OpenGL texture, and configures its parameters
	myPhoto.texUnit(shaderProgram, "tex0", 0); // This is how the fragment shader knows which texture to sample when it sees uniform sampler2D tex0
	
	//to add animation to the texture from glsl fragment shader 
	GLuint u_timeLoc = glGetUniformLocation(shaderProgram.ID, "u_time");
	GLuint u_mousePosLoc = glGetUniformLocation(shaderProgram.ID, "u_mousePos");
	// GLuint u_basicTextureLocation = glGetUniformLocation(shaderProgram.ID, "basictexture");

	// Create Input Controller & connect to the Glfw
	Input_Controller controller;
	glfwSetWindowUserPointer(window, &controller);
	glfwSetMouseButtonCallback(window, Input_Controller::mouseButtonCallback);

	// ---------------------------------------------------------------------------------- //
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	// ---------------------------------------------------------------------------------- //


	//float lastFrameTime = glfwGetTime();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		float clickTime = controller.getLastClickTime();
		glm::vec2 clickPos = controller.getLastClickPos();
		glUniform1f(u_timeLoc, clickTime);
		glUniform2f(u_mousePosLoc, clickPos.x, clickPos.y);

		glActiveTexture(GL_TEXTURE0);

		//update the time uniform
		float timeValue = glfwGetTime(); // Gets the current time
		glUniform1f(u_timeLoc, timeValue);

		// Specify the color of the background
		glClearColor(0.75f, 0.07f, 0.12f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);	// Clean the back buffer and assign the new color to it

		shaderProgram.Activate(); // Tell OpenGL which Shader Program we want to use

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);  // passing the time to the fragment shader 

		myPhoto.Bind(); 	// Binds texture so that is appears in rendering
		VAO1.Bind();	// Bind the VAO so OpenGL knows to use it

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);	// Swap the back buffer with the front buffer
		glfwPollEvents();	// Take care of all GLFW events

	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	myPhoto.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;

	} catch (int e) {
		std::cerr << "Caught exception: " << e << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Caught std::exception: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Caught unknown exception" << std::endl;
	}
}