#define BLASTCORE_IMPLEMENTATION
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdio.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

GLFWwindow* InitWindow(const int WinodwWidth, const int WindowHeight, const char *Title);
void InitVulkan(VkInstance *instance, const char* AppName, uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch);
void DestroyVulcanAndWindow(GLFWwindow *Window, VkInstance instance);

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

void InitVulkan(VkInstance *instance, const char* AppName, uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch) {
    VkApplicationInfo appInfo = {0};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = AppName;
    appInfo.applicationVersion = VK_MAKE_VERSION(VersionMajor, VersionMinor, VersionPatch);
    appInfo.pEngineName = "Blast Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;
    

    if (vkCreateInstance(&createInfo, NULL, instance) != VK_SUCCESS) {
        printf("failed to create instance!\n");
    }
}


void DestroyVulcanAndWindow(GLFWwindow *Window, VkInstance instance) {
    vkDestroyInstance(instance, NULL);
    glfwDestroyWindow(Window);
    glfwTerminate();
}