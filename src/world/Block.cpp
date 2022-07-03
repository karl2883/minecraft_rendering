#include "Block.h"

Block::Block(BlockType nBlockType) {
    blockType = nBlockType;
    UpdateAttributes();
}

void Block::SetBlockType(BlockType nBlockType) {
    blockType = nBlockType;
    UpdateAttributes();
}

void Block::UpdateAttributes() {
    isTransparent = false;
    if (blockType == BlockType::AIR || blockType == BlockType::LEAVES || blockType == BlockType::WATER) {
        isTransparent = true;
    }

    isFullyTransparent = false;
    if (blockType == BlockType::LEAVES) {
        isFullyTransparent = true;
    }
}
