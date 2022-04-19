#pragma once

#include <array>
#include "Block.h"
#include "../gfx/Renderer.h"
#include "../gfx/TextureHandler.h"
#include "ChunkMesh.h"

#define CHUNK_SIZE_X 16 
#define CHUNK_SIZE_Y 16 
#define CHUNK_SIZE_Z 16 

#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)
#define CHUNK_LAYER_SIZE (CHUNK_SIZE_X * CHUNK_SIZE_Z)

class Chunk {
    private:
        std::array<Block, CHUNK_VOLUME> data;
        glm::vec3 pos;
        glm::mat4 model;
        ChunkMesh mesh;
    public:
        Chunk(glm::vec3& pos, TextureHandler& textureHandler);
        void Generate();
        void GenerateMesh(TextureHandler& textureHandler);
        bool InBounds(int x, int y, int z) const;
        bool NextBlockEmpty(const Block& block, const glm::vec3& pos, int direction);

        int GetDataPos(int x, int y, int z) const;
        Block& GetBlock(int x, int y, int z);
        glm::vec3& GetPos() { return pos; }
        glm::mat4& GetModel() { return model; }
        ChunkMesh& GetMesh() { return mesh; }

        void Delete() { mesh.GetVAO().Delete(); }
};
