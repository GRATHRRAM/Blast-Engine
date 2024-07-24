#include "Blast.h"

int main() {
    GLFWwindow *window = InitWindow(1280,720,"Vulcan");
    VkInstance instance = {0}; 
    InitVulkan(&instance,"BlastTest", 1,0,0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    DestroyVulcanAndWindow(window, instance);
    return 0;
}
