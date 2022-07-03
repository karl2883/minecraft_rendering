#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* setup(int width, int height, GLDEBUGPROC debugfun, GLFWframebuffersizefun resizefun, GLFWcursorposfun cursorfun) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW Window!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing GLEW!" << std::endl;
        return nullptr;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugfun, nullptr);
    //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, false);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, resizefun);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // change to 0 for unlimited FPS (may make noise for graphics card LOL)
    glfwSwapInterval(0);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, cursorfun);
    return window;
}
