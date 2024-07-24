#include "Blast.h"

int main() {
    GLFWwindow *window = InitWindow(1280,720,"Vulcan");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    CloseWindow(window);

    return 0;
}
