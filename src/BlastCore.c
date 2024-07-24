#define BLASTCORE_IMPLEMENTATION
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

GLFWwindow* InitWindow(const int WinodwWidth, const int WindowHeight, const char *Title);
void CloseWindow(GLFWwindow *Window);

GLFWwindow* InitWindow(const int width,const int height, const char* title) {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }

    // Set the GLFW window hints (optional)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL major version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL minor version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core profile
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Allow window resizing

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    return window;
}


void CloseWindow(GLFWwindow *Window) {
    glfwDestroyWindow(Window);
    glfwTerminate();
}