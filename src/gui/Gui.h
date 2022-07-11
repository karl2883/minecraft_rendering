#pragma once

#include "../model/VertexArray.h"
#include "../gfx/Texture.h"
#include "../gfx/Renderer.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class GUI {
private:
    VertexArray squareVAO;

    Texture crosshairTexture;
    glm::mat4 crosshairModel;

    Renderer& renderer;
public:
    GUI(Renderer& renderer);
    void Render(); 
};
