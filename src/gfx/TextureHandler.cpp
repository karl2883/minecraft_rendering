#include "TextureHandler.h"

TextureHandler::TextureHandler(char* grassTexturePath) {
    int nr_channels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(grassTexturePath, &width, &height, &nr_channels, 0);

    // just assuming this for now
    format = GL_RGBA;
    rows = 10;
    cols = 10;
    image_size = 16;

    texture = Texture{data, width, height, format};
}

Texture& TextureHandler::GetTexture()  {
    return texture;
}

std::vector<glm::vec2> TextureHandler::GetTextureCoordinates(BlockType blockType, int side) {
    switch (blockType) {
    case BlockType::AIR:
        throw "Can't render air!";
    case BlockType::DIRT:
        return GetCoordinates(0, 5);
    case BlockType::GRASS:
        return GetCoordinates(0, side);
    case BlockType::STONE:
        return GetCoordinates(0, 6);
    case BlockType::WOOD:
        if (side == 0 ||side == 5) {
            return GetCoordinates(0, 8);
        } else {
            return GetCoordinates(0, 7);
        }
    case BlockType::LEAVES:
        return GetCoordinates(0, 9);
    default:
        throw "Unknown block type! (texture manager)";
    }
}

std::vector<glm::vec2> TextureHandler::GetCoordinates(int row, int col) const {
    // invert the row (from top=0 to bottom=0)
    row = rows - 1 - row;
    // just accept this function
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

