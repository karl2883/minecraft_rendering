#pragma once

class Chunk;

#include "Structure.h"
#include "NoiseGenerator.h"
#include "HeightMap.h"

class ChunkGenerator {
private:
    int m_seed;

    NoiseGenerator noiseGenerator;

    void GenerateGround(Chunk& chunk, HeightMap& heightMap);
    void GenerateTrees(Chunk& chunk, HeightMap& heightMap);

    Structure CreateTree(glm::vec3 pos);
    bool DoesStructureFit(Structure& structure, Chunk& chunk);
    void BuildStructure(Structure& structure, Chunk& chunk);
public:
    ChunkGenerator(int seed);
    void GenerateChunk(Chunk& chunk);
};

#include "Chunk.h"
