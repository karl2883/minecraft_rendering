#pragma once

#include <glm/glm.hpp>

enum BlockType {
    GRASS,
    DIRT,
    AIR
};

class Block {
private:
    BlockType blockType;
public:
    Block() {};
    Block(BlockType nBlockType) { blockType = nBlockType; }

    BlockType GetBlockType() const { return blockType; }
    void SetBlockType(BlockType nBlockType) { blockType = nBlockType; }
};

