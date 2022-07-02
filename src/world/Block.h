#pragma once

enum BlockType {
    STONE,
    GRASS,
    DIRT,
    WOOD,
    LEAVES,
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

