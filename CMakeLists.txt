cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(midterm)

# Include directories
include_directories(include)
include_directories(external)

# Add source files
add_executable(midterm 
    src/main.cpp
    src/shaderClass.cpp
    src/Texture.cpp
    src/VAO.cpp 
    src/VBO.cpp 
    src/EBO.cpp
    src/stb_image.cpp
    src/Input_Controller.cpp
    external/glad/glad.c
    external/glm/glm.hpp
)

# Find and link OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED CONFIG)

# Link GLFW and OpenGL
target_link_libraries(midterm 
    glfw
    OpenGL::GL
)
