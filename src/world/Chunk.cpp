#include "Chunk.h"
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <stdlib.h>

using namespace WorldConstants;

Chunk::Chunk(glm::vec3& xpos, TextureHandler& textureHandler, NoiseGenerator& noiseGenerator, World* world) 
    :pos(xpos), mesh(textureHandler), model(1.0f), world(world), heightMap(xpos.x, xpos.z, noiseGenerator)
{
    model = glm::translate(model, pos);
    Generate(noiseGenerator);
    mesh_has_generated = false;
}

void Chunk::Generate(NoiseGenerator& noiseGenerator) {
    FillAir();
    GenerateGround();
    GenerateTrees();
}

void Chunk::FillAir() {
    for (int x=0; x<CHUNK_SIZE_XZ; x++) {
        for (int y=0; y<CHUNK_SIZE_Y; y++) {
            for (int z=0; z<CHUNK_SIZE_XZ; z++) {
                Block newBlock { BlockType::AIR };
                data[GetDataPos(x, y, z)] = newBlock;
            }
        }
    }
}

void Chunk::GenerateGround() {
    for (int x=0; x<CHUNK_SIZE_XZ; x++) {
        for (int z=0; z<CHUNK_SIZE_XZ; z++) {
            int height = heightMap.GetHeight(x, z);
            for (int y=height-3; y<=height; y++) {
                if (height >= 0) {
                    GetBlock(x, y, z).SetBlockType(BlockType::DIRT);
                }
            }
            for (int y=0; y<height-3; y++) {
                GetBlock(x, y, z).SetBlockType(BlockType::STONE);
            }
            GetBlock(x, height, z).SetBlockType(BlockType::GRASS);
        }
    }
}

void Chunk::GenerateTrees() {
    for (int x=0; x<CHUNK_SIZE_XZ; x++) {
        for (int z=0; z<CHUNK_SIZE_XZ; z++) {
            if (rand() / (double)RAND_MAX < TREE_ODDS) {
                int height = heightMap.GetHeight(x, z); 
                if (height + 5 < CHUNK_SIZE_Y) {
                    for (int y=height; y<height+5; y++) {
                        GetBlock(x, y, z).SetBlockType(BlockType::WOOD);
                    }
                }
            }
        }
    }
}

void Chunk::GenerateMesh(TextureHandler& textureHandler) {
    mesh_has_generated = true;
    mesh.Clear();
    Block block;
    glm::vec3 bpos;
    for (int i=0; i<CHUNK_SIZE_XZ; i++) {
        for (int j=0; j<CHUNK_SIZE_Y; j++) {
            for (int k=0; k<CHUNK_SIZE_XZ; k++) {
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
            } else {
                return false;
            }
        }
        return true;
    }
}

bool Chunk::InBounds(int x2, int y2, int z2) const {
    if (0 <= x2 && x2 < CHUNK_SIZE_XZ) {
        if (0 <= y2 && y2 < CHUNK_SIZE_Y) {
            if (0 <= z2 && z2 < CHUNK_SIZE_XZ) {
                return true;
            }
        }
    }
    return false;
}

bool Chunk::OnBorder(int x, int y, int z) const {
    return x == 0 || x == CHUNK_SIZE_XZ-1 || z == 0 || z == CHUNK_SIZE_XZ-1;
}

std::vector<glm::vec2> Chunk::GetNeighbourChunkOffsets(int x, int y, int z) const {
    std::vector<glm::vec2> offsets;
    if (x == 0) {
        offsets.push_back(glm::vec2(-1, 0));
    }
    if (x == CHUNK_SIZE_XZ-1) {
        offsets.push_back(glm::vec2(1, 0));
    }
    if (z == 0) {
        offsets.push_back(glm::vec2(0, -1));
    }
    if (z == CHUNK_SIZE_XZ-1) {
        offsets.push_back(glm::vec2(0, 1));
    }
    return offsets;
}

int Chunk::GetDataPos(int x, int y, int z) const {
    return y*CHUNK_LAYER_SIZE+x*CHUNK_SIZE_XZ+z;
}

Block& Chunk::GetBlock(int x, int y, int z) {
    return data[y*CHUNK_LAYER_SIZE+x*CHUNK_SIZE_XZ+z];
}
