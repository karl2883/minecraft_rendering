#pragma once

#include "Chunk.h"
#include "../gfx/Renderer.h"
#include <algorithm>
#include <functional>

class World {
private:
    std::vector<std::vector<Chunk>> chunks;

    int x_low;
    int x_high;
    int z_low;
    int z_high;

    TextureHandler& textureHandler;
    static const int RENDER_DISTANCE = 3;
public:
    World(const glm::vec3& pos, TextureHandler& textureHandler);
    
    void InitializeChunks(const glm::vec3& pos);
    void UpdateChunks(const glm::vec3& pos);
    void AddChunks(int xl, int xh, int zl, int zh);
    void AddChunksX(int xl, int xh);
    void AddChunksZ(int zl, int zh);
    void RemoveRedundantChunks();
    void Render(Renderer& renderer);

    bool BlockInBounds(const glm::vec3& pos);
    Block& GetBlock(const glm::vec3& pos);
};
