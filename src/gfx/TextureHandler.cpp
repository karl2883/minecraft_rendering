#include "TextureHandler.h"

TextureHandler::TextureHandler(char* grassTexturePath) {
    int nr_channels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(grassTexturePath, &width, &height, &nr_channels, 0);

    // just assuming this for now
    format = GL_RGBA;
    rows = 2;
    cols = 3;
    image_size = 16;

    texture = Texture{data, width, height, format};
}

Texture& TextureHandler::GetTexture()  {
    return texture;
}

std::vector<glm::vec2> TextureHandler::GetSideCoordinates(int side) const {
    // swapping 0 and 1
    int row = rows - (side / cols) - 1;
    int col = side % cols;
    // for loops with two iterations each
    std::vector<glm::vec2> coordVec;
    for (int x=col*image_size; x<=(col+1)*image_size; x += image_size) {
        for (int y=(row+1)*image_size; y>=row*image_size; y -= image_size) {
             // make sure the result is a float
            glm::vec2 pos {(float)x/(float)width, (float)y/(float)height};
            coordVec.push_back(pos);
        }
    }
    return coordVec;
}
