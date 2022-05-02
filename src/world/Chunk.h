#pragma once

#include <array>
#include <functional>
#include "Block.h"
#include "../gfx/TextureHandler.h"
#include "ChunkMesh.h"


static const int CHUNK_SIZE_X = 16;
static const int CHUNK_SIZE_Y = 16;
static const int CHUNK_SIZE_Z = 16;
static const int CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;
static const int CHUNK_LAYER_SIZE = CHUNK_SIZE_X * CHUNK_SIZE_Z;

class World;

class Chunk {
    private:
        std::array<Block, CHUNK_VOLUME> data;
        glm::vec3 pos;
        glm::mat4 model;
        ChunkMesh mesh;

        std::array<Chunk*, 4> neighbouringChunks;

        World* world;
    public:
        Chunk(glm::vec3& pos, TextureHandler& textureHandler, World* world);
        void Generate();
        void GenerateMesh(TextureHandler& textureHandler);
        
        bool InBounds(int x, int y, int z) const;
        bool OnBorder(int x, int y, int z) const;
        std::vector<glm::vec2> GetNeighbourChunkOffsets(int x, int y, int z) const;
        bool NextBlockEmpty(const Block& block, const glm::vec3& pos, int direction);

        int GetDataPos(int x, int y, int z) const;
        Block& GetBlock(int x, int y, int z);
        glm::vec3& GetPos() { return pos; }
        glm::mat4& GetModel() { return model; }
        ChunkMesh& GetMesh() { return mesh; }

        void Delete() { mesh.GetVAO().Delete(); }
};

#include "World.h"
