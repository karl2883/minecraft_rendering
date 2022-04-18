#define STB_IMAGE_IMPLEMENTATION
#include "Game.h"
#include <GLFW/glfw3.h>
#include "debug.h"
#include "window.h"
#include "callbacks.h"
#include <iostream>


int main() {
    int width = 800;
    int height = 600;
    GLFWwindow* window = setup(width, height, DebugMessageCallback, framebuffer_resize_callback, mouse_callback); 

    Game game(window);
    game.Run();

	return 0;
}
