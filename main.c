#include "Blast.h"

int main() {
    Blast bl = {0};
    InitBlast(&bl, 1280, 720, "Blast Engine", "test",1,0,0);

    while (!glfwWindowShouldClose(bl.window)) {
        glfwPollEvents();
    }

    DestroyBlast(&bl);
    return 0;
}
