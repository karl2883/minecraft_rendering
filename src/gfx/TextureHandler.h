#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include <GL/glew.h>
#include "../world/Block.h"
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

    std::vector<glm::vec2> GetCoordinates(int row, int col) const;
public:
    TextureHandler(char* grassTexturePath);
    Texture& GetTexture();
    // x/y coordinates between 0 and 1 for a texture in the atlas (for shader)
    std::vector<glm::vec2> GetTextureCoordinates(BlockType blockType, int side);
};
