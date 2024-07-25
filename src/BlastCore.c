#define BLASTCORE_IMPLEMENTATION
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

typedef struct Blast {
    GLFWwindow *window;
    VkInstance instance;
    VkDevice device;
    VkPhysicalDevice pdevice;
} Blast;

typedef struct QueueFamilyIndices {
    uint32_t graphicsFamily;
} QueueFamilyIndices;


//header

void InitBlast(Blast *_Blast, const int WinodwWidth, const int WindowHeight,const char *Title,const char* AppName,
uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch);
void DestroyBlast(Blast *_Blast);

//hidden
GLFWwindow* InitWindow(const int WinodwWidth, const int WindowHeight, const char *Title);
VkInstance InitVulkan(const char* AppName, uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch);

VkPhysicalDevice PickPhysicalDevice(VkInstance instance);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
bool isDeviceSuitable(VkPhysicalDevice device);
VkDevice CreateLogicalDevice(VkPhysicalDevice physicalDevice);

void InitBlast(Blast *_Blast, const int WinodwWidth, const int WindowHeight,const char *Title,const char* AppName,
uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch) {
    _Blast->window = InitWindow(WinodwWidth, WindowHeight, Title);
    _Blast->instance = InitVulkan(AppName, VersionMajor, VersionMinor, VersionPatch);
    _Blast->pdevice = PickPhysicalDevice(_Blast->instance);
    _Blast->device = CreateLogicalDevice(_Blast->pdevice);
}

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

VkInstance InitVulkan(const char* AppName, uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch) {
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
    
    VkInstance instance = 0;

    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        printf("failed to create instance!\n");
        return NULL;
    }
    return instance;
}

VkPhysicalDevice PickPhysicalDevice(VkInstance instance) {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;

    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    if (deviceCount == 0) {
        printf("failed to find GPUs with Vulkan support!");
        return NULL;
    }

    VkPhysicalDevice *dev = (VkPhysicalDevice*) malloc(sizeof(VkPhysicalDevice) * deviceCount);

    if(dev == NULL) {
        printf("failed to Allocate space for VkPhysicalDevice *dev");
        return NULL;
    }

    vkEnumeratePhysicalDevices(instance, &deviceCount,  dev);

    for(uint64_t i = 0; i < deviceCount; ++i) {
        if (isDeviceSuitable(dev[i])) {
            physicalDevice = dev[i];
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        printf("failed to find a suitable GPU!");
    }

    free(dev);
    return physicalDevice;
}

bool isDeviceSuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    QueueFamilyIndices indices = findQueueFamilies(device);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
    deviceFeatures.geometryShader && indices.graphicsFamily != 0;
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices = {0};

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

    VkQueueFamilyProperties *queueFamilies = (VkQueueFamilyProperties*)
    malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

    for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }
    }

    if(indices.graphicsFamily == 0) {
        printf("indices.graphicsFamily == 0");
    }

    free(queueFamilies);
    return indices;
}

VkDevice CreateLogicalDevice(VkPhysicalDevice physicalDevice) {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo = {0};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures = {0};

    VkDeviceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;
    createInfo.enabledLayerCount = 0;

    VkDevice device = NULL;

    if (vkCreateDevice(physicalDevice, &createInfo, NULL, &device) != VK_SUCCESS) {
        printf("failed to create logical device!");
    }

    return device;
}

void DestroyBlast(Blast *_Blast) {
    vkDestroyDevice(_Blast->device, NULL);
    vkDestroyInstance(_Blast->instance, NULL);
    glfwDestroyWindow(_Blast->window);
    glfwTerminate();
}