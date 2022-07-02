#pragma once

class Chunk;
class World;

#include "Structure.h"
#include "NoiseGenerator.h"
#include "HeightMap.h"

class ChunkGenerator {
private:
    int seed;

    NoiseGenerator noiseGenerator;

    std::vector<Structure> structureOverhangs;

    World* world;

    void GenerateGround(Chunk& chunk, HeightMap& heightMap);
    void GenerateTrees(Chunk& chunk, HeightMap& heightMap);

    Structure CreateTree(glm::vec3 pos);
    bool DoesStructureFit(Structure& structure, Chunk& chunk);
    void BuildStructure(Structure& structure, Chunk& chunk);
public:
    ChunkGenerator(int seed, World* world);
    void GenerateChunk(Chunk& chunk);
};

#include "Chunk.h"
#include "World.h"
