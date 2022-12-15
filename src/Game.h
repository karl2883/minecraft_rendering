#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "gui/Gui.h"
#include "player/Camera.h"
#include "player/Player.h"
#include "world/World.h"
#include "gfx/TextureHandler.h"
#include "util/FPSCounter.h"

class Game {
private:
    GLFWwindow* window;

    FPSCounter fpsCounter;

    float visibility;
    int width;
    int height;

    TextureHandler textureHandler;

    World world;

    Player player;

    Renderer renderer;

    GUI gui;

    float deltaTime;
    float lastFrame;

    bool firstMouse;

    bool mouseLeftPressedLastFrame;
    bool mouseRightPressedLastFrame;

    float lastx;
    float lasty;
public:
    Game(GLFWwindow* window);
    void ScrollCallback(const GLFWwindow* window, double xoffset, double yoffset);
    void MouseCallback(const GLFWwindow* window, double xpos, double ypos);
    void Resize(int nwidth, int nheight) { width=nwidth; height=nheight; glViewport(0, 0, width, height); };
    void ProcessInput(GLFWwindow* window);
    void Run();

    bool ShouldRun() const;
    void UpdateEvents();

    Renderer& GetRenderer() { return renderer; }
};
