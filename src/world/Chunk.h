#pragma once

#include <array>
#include <functional>
#include <noise/noise.h>
#include "Block.h"
#include "../gfx/TextureHandler.h"
#include "ChunkMesh.h"
#include "NoiseGenerator.h"


constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 128;
constexpr int CHUNK_SIZE_Z = 16;
constexpr int CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;
constexpr int CHUNK_LAYER_SIZE = CHUNK_SIZE_X * CHUNK_SIZE_Z;

class World;

class Chunk {
    private:
        std::array<Block, CHUNK_VOLUME> data;
        glm::vec3 pos;
        glm::mat4 model;
        ChunkMesh mesh;

        bool mesh_has_generated;

        World* world;
    public:
        Chunk(glm::vec3& pos, TextureHandler& textureHandler, NoiseGenerator& noiseGenerator, World* world);
        void Generate(NoiseGenerator& noiseGenerator);
        void GenerateMesh(TextureHandler& textureHandler);
        
        bool InBounds(int x, int y, int z) const;
        bool OnBorder(int x, int y, int z) const;
        std::vector<glm::vec2> GetNeighbourChunkOffsets(int x, int y, int z) const;
        bool NextBlockEmpty(const Block& block, const glm::vec3& pos, int direction);

        bool MeshGenerated() { return mesh_has_generated; }

        int GetDataPos(int x, int y, int z) const;
        Block& GetBlock(int x, int y, int z);
        glm::vec3& GetPos() { return pos; }
        glm::mat4& GetModel() { return model; }
        ChunkMesh& GetMesh() { return mesh; }

        void Delete() { mesh.GetVAO().Delete(); }
};

#include "World.h"
