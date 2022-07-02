#pragma once

#include "Block.h"
#include "glm/glm.hpp"
#include "../util/Vector3D.h"

class Structure {
private:
    glm::vec3 m_pos;
    glm::vec3 m_size;

    Vector3D<BlockType> m_blocks;
public:
    Structure(glm::vec3 pos, glm::vec3 size, Vector3D<BlockType> blocks);
    Structure(Structure& structure, int cutoff_x, int cutoff_z);
    
    bool IsBlock(int x, int y, int z);
    BlockType GetBlock(int x, int y, int z);

    glm::vec3& GetPos() { return m_pos; };
    glm::vec3& GetSize() { return m_size; };
};
