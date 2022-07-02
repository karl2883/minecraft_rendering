#include "Structure.h"

Structure::Structure(glm::vec3 pos, glm::vec3 size, Vector3D<BlockType> blocks)
:m_blocks(blocks), m_size(size), m_pos(pos)
{}

bool Structure::IsBlock(int x, int y, int z) {
    return m_blocks.Get(x-m_pos.x, y-m_pos.y, z-m_pos.z) != BlockType::AIR;
}

BlockType Structure::GetBlock(int x, int y, int z) {
    return m_blocks.Get(x-m_pos.x, y-m_pos.y, z-m_pos.z);
}
