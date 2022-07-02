#include "Structure.h"

Structure::Structure(glm::vec3 pos, glm::vec3 size, Vector3D<BlockType> blocks)
:blocks(blocks), size(size), pos(pos)
{}

bool Structure::IsBlock(int x, int y, int z) {
    return blocks.Get(x-pos.x, y-pos.y, z-pos.z) != BlockType::AIR;
}

BlockType Structure::GetBlock(int x, int y, int z) {
    return blocks.Get(x-pos.x, y-pos.y, z-pos.z);
}
