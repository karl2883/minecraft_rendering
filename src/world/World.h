#pragma once

#include "Chunk.h"
#include "../gfx/Renderer.h"
#include <algorithm>
#include <functional>

class World {
private:
    std::vector<Chunk> chunks;

    int x_low;
    int x_high;
    int z_low;
    int z_high;

    TextureHandler& textureHandler;
    static const int RENDER_DISTANCE = 2;
public:
    World(const glm::vec3& pos, TextureHandler& textureHandler);
    
    void InitializeChunks(const glm::vec3& pos);
    void UpdateChunks(const glm::vec3& pos);
    void AddChunks(int xl, int xh, int zl, int zh);
    void RemoveChunks(int xl, int xh, int zl, int zh);
    void Render(Renderer& renderer);
    void AddChunk(glm::vec3& cpos);

    bool BlockInBounds(const glm::vec3& pos);
    Block& GetBlock(const glm::vec3& pos);
};
