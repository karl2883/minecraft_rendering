#include "Chunk.h"
#include <glm/gtx/string_cast.hpp>
#include <vector>

Chunk::Chunk(glm::vec3& xpos, TextureHandler& textureHandler, World* world) 
    :pos(xpos), mesh(textureHandler), model(1.0f), neighbouringChunks(), world(world)
{
    for (int a=0; a<4; a++) {
        neighbouringChunks[a] = nullptr;
    }
    model = glm::translate(model, pos);
    Generate();
}

void Chunk::Generate() {
    for (int i=0; i<CHUNK_SIZE_X; i++) {
        for (int j=0; j<CHUNK_SIZE_Y; j++) {
            for (int k=0; k<CHUNK_SIZE_Z; k++) {
                BlockType type;
                // I want a pyramid
                if (j == 7) {
                    type = BlockType::GRASS;
                } else if (j <= 7) {
                    type = BlockType::DIRT;
                } else {
                    type = BlockType::AIR;
                }
                Block newBlock { type };
                data[GetDataPos(i, j, k)] = newBlock;
            }
        }
    }
}

void Chunk::GenerateMesh(TextureHandler& textureHandler) {
    mesh.Clear();
    Block block;
    glm::vec3 bpos;
    for (int i=0; i<CHUNK_SIZE_X; i++) {
        for (int j=0; j<CHUNK_SIZE_Y; j++) {
            for (int k=0; k<CHUNK_SIZE_Z; k++) {
                block = GetBlock(i, j, k);
                bpos.x = i;
                bpos.y = j;
                bpos.z = k;
                if (block.GetBlockType() != BlockType::AIR) {
                    for (int side=0; side<6; side++) {
                        if (NextBlockEmpty(block, bpos, side)) {
                            mesh.AddFace(block, bpos, side, textureHandler);
                        }
                    }
                }
            }
        }
    }
    mesh.BuildMesh();
}

bool Chunk::NextBlockEmpty(const Block& block, const glm::vec3& bpos, int direction) {
    int x = bpos.x;
    int y = bpos.y;
    int z = bpos.z;
    switch(direction) {
    case 0:
        y += 1;
        break;
    case 1:
        x += 1;
        break;
    case 2:
        z -= 1;
        break;
    case 3:
        z += 1;
        break;
    case 4:
        x -= 1;
        break;
    case 5:
        y -= 1;
        break;
    }
    if (InBounds(x, y, z)) {
        Block& nextBlock = GetBlock(x, y, z);
        return nextBlock.GetBlockType() == BlockType::AIR;
    } else {
        if (direction != 0 && direction != 5) {
            glm::vec3 abs_bpos = glm::vec3(x, y, z) + pos;
            if (world->BlockInBounds(abs_bpos)) {
                if (world->GetBlock(abs_bpos).GetBlockType() != BlockType::AIR) {
                    return false;
                }                
            }
        }
        return true;
    }
}

bool Chunk::InBounds(int x2, int y2, int z2) const {
    if (0 <= x2 && x2 < CHUNK_SIZE_X) {
        if (0 <= y2 && y2 < CHUNK_SIZE_Y) {
            if (0 <= z2 && z2 < CHUNK_SIZE_Z) {
                return true;
            }
        }
    }
    return false;
}

int Chunk::GetDataPos(int x, int y, int z) const {
    return y*CHUNK_LAYER_SIZE+x*CHUNK_SIZE_Z+z;
}

Block& Chunk::GetBlock(int x, int y, int z) {
    return data[y*CHUNK_LAYER_SIZE+x*CHUNK_SIZE_Z+z];
}
