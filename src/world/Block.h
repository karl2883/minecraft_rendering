#pragma once

#include <glm/glm.hpp>

enum BlockType {
    GRASS,
    AIR
};

class Block {
private:
    BlockType blockType;
public:
    Block() {};
    Block(BlockType nBlockType) { blockType = nBlockType; }

    BlockType getBlockType() const { return blockType; }
};

