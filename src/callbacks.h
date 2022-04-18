#pragma once

#include "Game.h"

Game* getGame(GLFWwindow* win);
void framebuffer_resize_callback(GLFWwindow* window, int newwidth, int newheight);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

