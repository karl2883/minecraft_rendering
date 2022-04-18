#pragma once

#include <array>
#include "Block.h"
#include "../gfx/Renderer.h"
#include "../gfx/TextureHandler.h"
#include "ChunkMesh.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define CHUNK_LAYER_SIZE (CHUNK_SIZE_X * CHUNK_SIZE_Z)

class Chunk {
    private:
        int x;
        int y;
        int z;
        std::array<Block, CHUNK_VOLUME> data;
        Renderer& renderer;
        ChunkMesh mesh;
        glm::mat4 model;
    public:
        Chunk(int x, int y, int z, Renderer& renderer);
        void Generate();
        void GenerateMesh();
        void Render();
        bool InBounds(int x, int y, int z) const;
        bool NextBlockEmpty(const Block& block, const glm::vec3& pos, int direction);

        int GetDataPos(int x, int y, int z) const;
        Block& GetBlock(int x, int y, int z);
};
