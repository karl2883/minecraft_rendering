#pragma once

class Chunk;

#include "NoiseGenerator.h"
#include "HeightMap.h"

class ChunkGenerator {
private:
    NoiseGenerator noiseGenerator;

    void GenerateGround(Chunk& chunk, HeightMap& heightMap);
    void GenerateTrees(Chunk& chunk, HeightMap& heightMap);
public:
    ChunkGenerator(int seed);
    void GenerateChunk(Chunk& chunk);
};

#include "Chunk.h"
