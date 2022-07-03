#pragma once

#include <array>
#include <functional>
#include "Block.h"
#include "Constants.h"
#include "../gfx/TextureHandler.h"
#include "ChunkMesh.h"


// I pretty much have to have a circular reference here (neighbour chunks), that's why forward declaration
class World;

class Chunk {
    private:
        std::array<Block, WorldConstants::CHUNK_VOLUME> data;
        glm::vec3 pos;
        glm::mat4 model;
        ChunkMesh mesh;

        bool mesh_has_generated;

        World* world;

        bool NextBlockTransparent(const Block& block, const glm::vec3& pos, int direction);
        int GetDataPos(int x, int y, int z) const;

        void FillAir();
    public:
        Chunk(glm::vec3& pos, TextureHandler& textureHandler, World* world);
        void GenerateMesh(TextureHandler& textureHandler);
        
        bool InBounds(int x, int y, int z) const;
        bool OnBorder(int x, int y, int z) const;
        std::vector<glm::vec2> GetNeighbourChunkOffsets(int x, int y, int z) const;

        bool MeshGenerated() { return mesh_has_generated; }

        Block& GetBlock(int x, int y, int z);
        glm::vec3& GetPos() { return pos; }
        glm::mat4& GetModel() { return model; }
        ChunkMesh& GetMesh() { return mesh; }

        void Delete() { mesh.GetVAO().Delete(); }
};

#include "World.h"
