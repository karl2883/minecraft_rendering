#include "Chunk.h"

using namespace WorldConstants;

Chunk::Chunk(glm::vec3& xpos, TextureHandler& textureHandler, World* world) 
    :pos(xpos), solid_mesh(textureHandler), transparent_mesh(textureHandler), model(1.0f), world(world)
{
    model = glm::translate(model, pos);
    FillAir();
    mesh_has_generated = false;
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

void Chunk::GenerateMesh(TextureHandler& textureHandler) {
    mesh_has_generated = true;
    solid_mesh.Clear();
    transparent_mesh.Clear();
    Block block;
    glm::vec3 bpos;
    for (int x=0; x<CHUNK_SIZE_XZ; x++) {
        for (int y=0; y<CHUNK_SIZE_Y; y++) {
            for (int z=0; z<CHUNK_SIZE_XZ; z++) {
                block = GetBlock(x, y, z);
                bpos.x = x;
                bpos.y = y;
                bpos.z = z;
                if (block.GetBlockType() != BlockType::AIR) {
                    for (int side=0; side<6; side++) {
                        if (NextBlockTransparent(block, bpos, side)) {
                            if (block.IsTransparent() && block.GetBlockType() != BlockType::LEAVES) {
                                transparent_mesh.AddFace(block, bpos, side, textureHandler);
                            } else {
                                solid_mesh.AddFace(block, bpos, side, textureHandler);
                            }
                        }
                    }
                }
            }
        }
    }
    solid_mesh.BuildMesh();
    transparent_mesh.BuildMesh();
}

bool Chunk::NextBlockTransparent(const Block& block, const glm::vec3& bpos, int direction) {
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
        return (nextBlock.IsTransparent() && block.GetBlockType() != nextBlock.GetBlockType()) || nextBlock.IsFullyTransparent();
    } else {
        if (direction != 0 && direction != 5) {
            glm::vec3 abs_bpos = glm::vec3(x, y, z) + pos;
            if (world->BlockInBounds(abs_bpos)) {
                if (world->GetBlock(abs_bpos).IsTransparent() && block.GetBlockType() != world->GetBlock(abs_bpos).GetBlockType()) {
                    return true;
                } else if (world->GetBlock(abs_bpos).IsFullyTransparent()) {
                    return true;
                } else return false;                
            } else return false;
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
