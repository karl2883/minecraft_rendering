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
    if (blockType == BlockType::AIR || blockType == BlockType::LEAVES || blockType == BlockType::WATER) {
        isTransparent = true;
    } else {
        isTransparent = false;
    }
}
