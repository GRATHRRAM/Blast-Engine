#ifndef BLAST_H
#define BLAST_H
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

typedef struct Blast {
    GLFWwindow *window;
    VkInstance instance;
    VkDevice device;
    VkPhysicalDevice pdevice;
} Blast;

void InitBlast(Blast *_Blast, const int WinodwWidth, const int WindowHeight,const char *Title,const char* AppName,
uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch);

void DestroyBlast(Blast *_Blast);
#endif