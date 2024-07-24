#include "Blast.h"

int main() {
    GLFWwindow *Window = InitWindow(1280,720,"Vulcan");

     while(!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
    }

    CloseWindow(Window);

    return 0;
}
