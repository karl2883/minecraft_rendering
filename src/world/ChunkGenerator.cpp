#include "ChunkGenerator.h"

using namespace WorldConstants;

ChunkGenerator::ChunkGenerator(int seed)
:noiseGenerator(seed)
{
    // ...? 
}

void ChunkGenerator::GenerateChunk(Chunk& chunk) {
    HeightMap heightMap {(int)chunk.GetPos().x, (int)chunk.GetPos().z, noiseGenerator};
    GenerateGround(chunk, heightMap);
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
    for (int x=0; x<CHUNK_SIZE_XZ; x++) {
        for (int z=0; z<CHUNK_SIZE_XZ; z++) {
            if (rand() / (double)RAND_MAX < TREE_ODDS) {
                int height = heightMap.GetHeight(x, z); 
                if (height + 5 < CHUNK_SIZE_Y) {
                    for (int y=height; y<height+5; y++) {
                        chunk.GetBlock(x, y, z).SetBlockType(BlockType::WOOD);
                    }
                }
            }
        }
    }
}
