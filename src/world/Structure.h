#pragma once

#include "Block.h"
#include "Constants.h"
#include "glm/glm.hpp"
#include "../util/Vector3D.h"

class Structure {
private:
    glm::vec3 pos;
    glm::vec3 size;

    Vector3D<BlockType> blocks;
public:
    Structure(glm::vec3 pos, glm::vec3 size, Vector3D<BlockType> blocks);
    
    std::vector<Structure> CreateCutoffSubStructures(glm::vec3& original_cpos);

    bool IsBlock(int x, int y, int z);
    BlockType GetBlock(int x, int y, int z);

    glm::vec3& GetPos() { return pos; };
    glm::vec3& GetSize() { return size; };
};
