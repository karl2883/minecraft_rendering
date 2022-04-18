#include "Chunk.h"

Chunk::Chunk(int x, int y, int z, Renderer& renderer) 
    :x(x), y(y), z(z), renderer(renderer), mesh(renderer.GetTextureHandler()), model(1.0f)
{
    glm::translate(model, glm::vec3(x, y, z));
    Generate();
    GenerateMesh();
}

void Chunk::Generate() {
    for (int i=x; i<CHUNK_SIZE_X; i++) {
        for (int j=y; j<CHUNK_SIZE_Y; j++) {
            for (int k=z; k<CHUNK_SIZE_Z; k++) {
                BlockType type;
                // I want a pyramid
                if (j <= i && j <= k) {
                    type = BlockType::GRASS;
                } else {
                    type = BlockType::AIR;
                }
                Block newBlock { type };
                data[GetDataPos(i, j, k)] = newBlock;
            }
        }
    }
}

void Chunk::GenerateMesh() {
    Block block;
    glm::vec3 pos;
    for (int i=x; i<CHUNK_SIZE_X; i++) {
        for (int j=y; j<CHUNK_SIZE_Y; j++) {
            for (int k=z; k<CHUNK_SIZE_Z; k++) {
                block = GetBlock(i, j, k);
                pos.x = i;
                pos.y = j;
                pos.z = k;
                if (block.getBlockType() != BlockType::AIR) {
                    for (int side=0; side<6; side++) {
                        if (NextBlockEmpty(block, pos, side)) {
                            mesh.AddFace(block, pos, side);
                        }
                    }
                }
            }
        }
    }
    mesh.BuildMesh();
}

void Chunk::Render() {
    renderer.RenderMesh(mesh.GetVAO(), mesh.GetVertexCount(), model);
}

bool Chunk::NextBlockEmpty(const Block& block, const glm::vec3& pos, int direction) {
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;
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
        return nextBlock.getBlockType() == BlockType::AIR;
    } else {
        return true;
    }
}

bool Chunk::InBounds(int x2, int y2, int z2) const {
    if (x <= x2 && x2 < x + CHUNK_SIZE_X) {
        if (y <= y2 && y2 < y + CHUNK_SIZE_Y) {
            if (z <= z2 && z2 < z + CHUNK_SIZE_Z) {
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
