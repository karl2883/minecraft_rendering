#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include <GL/glew.h>
#include "stb_image.h"

class TextureHandler {
private:
    Texture texture;
    unsigned int format;
    int width;
    int height;
    int rows;
    int cols;
    int image_size; // quadratic
public:
    TextureHandler(char* grassTexturePath);
    Texture& GetTexture();
    // x/y coordinates between 0 and 1 for a texture in the atlas (for shader)
    std::vector<glm::vec2> GetGrassCoordinates(int side) const;
    std::vector<glm::vec2> GetDirtCoordinates(int side) const;
};
