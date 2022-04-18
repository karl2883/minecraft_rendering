#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* setup(int width, int height, GLDEBUGPROC debugfun, GLFWframebuffersizefun resizefun, GLFWcursorposfun cursorfun);
