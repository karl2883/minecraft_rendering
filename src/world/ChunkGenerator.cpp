#include "ChunkGenerator.h"
#include <cmath>

using namespace WorldConstants;

ChunkGenerator::ChunkGenerator(int seed, World* world)
:noiseGenerator(seed), world(world)
{
    this->seed = seed;
}

void ChunkGenerator::GenerateChunk(Chunk& chunk) {
    HeightMap heightMap {(int)chunk.GetPos().x, (int)chunk.GetPos().z, noiseGenerator};
    GenerateGround(chunk, heightMap);
    for (Structure& structure: structureOverhangs) {
        glm::vec3 cpos = structure.GetPos()-chunk.GetPos();
        if (chunk.InBounds(cpos.x, cpos.y, cpos.z)) {
            BuildStructure(structure, chunk);
        }
    }
    GenerateTrees(chunk, heightMap);
}

void ChunkGenerator::GenerateGround(Chunk& chunk, HeightMap& heightMap) {
    for (int x=0; x<CHUNK_SIZE_XZ; x++) {
        for (int z=0; z<CHUNK_SIZE_XZ; z++) {
            int height = heightMap.GetHeight(x, z);
            for (int y=height-3; y<=height; y++) {
                if (height >= 0) {
                    chunk.GetBlock(x, y, z).SetBlockType(BlockType::DIRT);
                }
            }
            for (int y=0; y<height-3; y++) {
                chunk.GetBlock(x, y, z).SetBlockType(BlockType::STONE);
            }
            chunk.GetBlock(x, height, z).SetBlockType(BlockType::GRASS);
        }
    }
}

void ChunkGenerator::GenerateTrees(Chunk& chunk, HeightMap& heightMap) {
    for (int x=-4; x<CHUNK_SIZE_XZ; x++) {
        for (int z=-4; z<CHUNK_SIZE_XZ; z++) {
            if (rand() / (double)RAND_MAX < TREE_ODDS) {
                int height = noiseGenerator.GetHeight(x, z, chunk.GetPos().x, chunk.GetPos().z); 
                glm::vec3 pos {chunk.GetPos().x+x, chunk.GetPos().y+height, chunk.GetPos().z+z};
                Structure tree = CreateTree(pos);
                if (DoesStructureFit(tree, chunk)) {
                    BuildStructure(tree, chunk);   
                    std::vector<Structure> overhangs = tree.CreateCutoffSubStructures(chunk.GetPos());
                    structureOverhangs.insert(structureOverhangs.end(), overhangs.begin(), overhangs.end());
                }
            }
        }
    }
}

bool ChunkGenerator::DoesStructureFit(Structure& structure, Chunk& chunk) {
    glm::vec3& pos = structure.GetPos();
    glm::vec3& size = structure.GetSize();
    for (int x=pos.x; x<pos.x+size.x; x++) {
        for (int y=pos.y; y<pos.y+size.y; y++) {
            for (int z=pos.z; z<pos.z+size.z; z++) {
                if (structure.IsBlock(x, y, z)) {
                    glm::vec3 pos {x, y, z};
                    glm::vec3 chunkPos = pos - chunk.GetPos();
                    if (chunk.InBounds(chunkPos.x, chunkPos.y, chunkPos.z)) {
                        if (chunk.GetBlock(chunkPos.x, chunkPos.y, chunkPos.z).GetBlockType() != BlockType::AIR) {
                            return false;
                        }
                    } else {
                        if (world->BlockInBounds(pos)) {
                            return false;
                        }
                        if (noiseGenerator.GetHeight(pos.x, pos.z)+Y_OFFSET >= pos.y) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void ChunkGenerator::BuildStructure(Structure& structure, Chunk& chunk) {
    glm::vec3& pos = structure.GetPos();
    glm::vec3& size = structure.GetSize();
    for (int x=pos.x; x<pos.x+size.x; x++) {
        for (int y=pos.y; y<pos.y+size.y; y++) {
            for (int z=pos.z; z<pos.z+size.z; z++) {
                if (structure.IsBlock(x, y, z)) {
                    glm::vec3 chunkPos = glm::vec3(x, y, z) - chunk.GetPos();
                    if (chunk.InBounds(chunkPos.x, chunkPos.y, chunkPos.z)) {
                        chunk.GetBlock(chunkPos.x, chunkPos.y, chunkPos.z).SetBlockType(structure.GetBlock(x, y, z));
                    }
                }
            }
        }
    }
}

Structure ChunkGenerator::CreateTree(glm::vec3 pos) {
    int log_size = 3 + std::abs((seed * ((int)pos.y ^ (int)pos.x) - ((int)pos.z >> 1))) % 3;

    glm::vec3 size {5, log_size+3, 5};

    Vector3D<BlockType> treeBlocks {size, BlockType::AIR};

    // Creating the base leaves (gets edited later)
    for (int y=log_size; y<log_size+2; y++) {
        for (int x=0; x<size.x; x++) {
            for (int z=0; z<size.z; z++) {
                treeBlocks.Set(x, y, z, BlockType::LEAVES);
            }
        }
    }

    // Creating the log
    for (int y=0; y<log_size+2; y++) {
        treeBlocks.Set(2, y, 2, BlockType::WOOD);
    }

    // Creating the leaves top (cross)
    int y = log_size+2;
    treeBlocks.Set(2, y, 2, BlockType::LEAVES);
    treeBlocks.Set(2, y, 1, BlockType::LEAVES);
    treeBlocks.Set(2, y, 3, BlockType::LEAVES);
    treeBlocks.Set(1, y, 2, BlockType::LEAVES);
    treeBlocks.Set(3, y, 2, BlockType::LEAVES);

    return Structure {pos, size, treeBlocks};
}
