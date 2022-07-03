#pragma once

enum BlockType {
    STONE,
    GRASS,
    DIRT,
    WOOD,
    LEAVES,
    WATER,
    AIR
};

class Block {
private:
    BlockType blockType;

    bool isTransparent;
    bool isFullyTransparent;

    void UpdateAttributes();
public:
    Block() {};
    Block(BlockType nBlockType);

    BlockType GetBlockType() const { return blockType; }
    void SetBlockType(BlockType nBlockType);

    bool IsTransparent() const { return isTransparent; }
    bool IsFullyTransparent() const { return isFullyTransparent; }
};

