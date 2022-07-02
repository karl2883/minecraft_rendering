#include "Structure.h"

using namespace WorldConstants;

Structure::Structure(glm::vec3 pos, glm::vec3 size, Vector3D<BlockType> blocks)
:blocks(blocks), size(size), pos(pos)
{}

int getNearestChunkBorder(int value) {
    int border = ((int)value / CHUNK_SIZE_XZ) * CHUNK_SIZE_XZ;
    if (border > value) {
        border -= CHUNK_SIZE_XZ;
    }
    return border;
}


std::vector<Structure> Structure::CreateCutoffSubStructures(glm::vec3& original_cpos) {
    int chunk_border_x_low = getNearestChunkBorder(pos.x);
    int chunk_border_z_low = getNearestChunkBorder(pos.z);
    int chunk_border_x_high = getNearestChunkBorder(pos.x+size.x);
    int chunk_border_z_high = getNearestChunkBorder(pos.z+size.z);

    std::vector<Structure> subsection_structures;

    for (int cx=chunk_border_x_low; cx<= chunk_border_x_high; cx += CHUNK_SIZE_XZ) {
        for (int cz=chunk_border_z_low; cz<= chunk_border_z_high; cz += CHUNK_SIZE_XZ) {
            if (!(cx == original_cpos.x && cz == original_cpos.z)) {
                int x_low = std::max(cx, (int)pos.x);
                int z_low = std::max(cz, (int)pos.z);
                int x_high = std::min(cx+CHUNK_SIZE_XZ, (int)pos.x+(int)size.x);
                int z_high = std::min(cz+CHUNK_SIZE_XZ, (int)pos.z+(int)size.z);

                glm::vec3 subsection_pos {x_low, pos.y, z_low};
                glm::vec3 subsection_size {x_high-x_low, size.y, z_high-z_low};
                Vector3D<BlockType> subsection_blocks {subsection_size, BlockType::AIR};

                for (int x=x_low; x<x_high; x++) {
                    for (int y=pos.y; y<pos.y+size.y; y++) {
                        for (int z=z_low; z<z_high; z++) {
                            subsection_blocks.Set(x-x_low, y-pos.y, z-z_low, GetBlock(x, y, z));
                        }
                    }
                }

                Structure subsection_structure {subsection_pos, subsection_size, subsection_blocks};
                subsection_structures.push_back(subsection_structure);
            }
        }
    }

    std::cout << subsection_structures.size() << std::endl;
    return subsection_structures;
}

bool Structure::IsBlock(int x, int y, int z) {
    return blocks.Get(x-pos.x, y-pos.y, z-pos.z) != BlockType::AIR;
}

BlockType Structure::GetBlock(int x, int y, int z) {
    return blocks.Get(x-pos.x, y-pos.y, z-pos.z);
}
