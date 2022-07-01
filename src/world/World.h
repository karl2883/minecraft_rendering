#pragma once

#include "Chunk.h"
#include "../gfx/Renderer.h"
#include "NoiseGenerator.h"
#include <algorithm>
#include <queue>
#include <functional>

class World {
private:
    std::vector<std::vector<Chunk>> chunks;

    int x_low_old;
    int x_high_old;
    int z_low_old;
    int z_high_old;

    int x_low;
    int x_high;
    int z_low;
    int z_high;

    std::queue<glm::vec2> mesh_generation_queue;

    TextureHandler& textureHandler;

    NoiseGenerator noiseGenerator;

    void InitializeChunks(const glm::vec3& pos);

    void RemoveRedundantChunks();
    void AddChunksX(int xn);
    void AddChunksZ(int zn);

    glm::vec2 GetChunkPos(glm::vec3& pos);
    glm::vec2 GetChunkPos(Chunk& chunk);
    Chunk& GetChunk(glm::vec3& pos);
    glm::vec3 GetBlockCoordinates(glm::vec3& pos);

    bool ChunkInBounds(const glm::vec2& pos);
public:
    World(const glm::vec3& pos, TextureHandler& textureHandler);
    
    void UpdateChunks(const glm::vec3& pos);
    void Render(Renderer& renderer);

    void SetBlock(glm::vec3 pos, BlockType newBlockType);

    bool BlockInBounds(const glm::vec3& pos);

    Block& GetBlock(glm::vec3& pos);
};
