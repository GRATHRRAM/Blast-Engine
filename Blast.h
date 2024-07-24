#ifndef BLAST_H
#define BLAST_H
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

GLFWwindow* InitWindow(const int WinodwWidth, const int WindowHeight, const char *Title);
void InitVulkan(VkInstance *instance, const char* AppName, uint32_t VersionMajor, uint32_t VersionMinor, uint32_t VersionPatch);
void DestroyVulcanAndWindow(GLFWwindow *Window, VkInstance instance);

#endif