#include "callbacks.h"

Game* getGame(GLFWwindow* win) {
    return (Game*) glfwGetWindowUserPointer(win);
}

void framebuffer_resize_callback(GLFWwindow* window, int newwidth, int newheight) {
    Game* game = getGame(window);
    game->Resize(newwidth, newheight);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Game* game = getGame(window);
    game->MouseCallback(window, xpos, ypos);
}
