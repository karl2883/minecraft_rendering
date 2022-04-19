#include "World.h"
#include <glm/gtx/string_cast.hpp>

World::World(const glm::vec3& pos, TextureHandler& textureHandler) 
:textureHandler(textureHandler)
{
    x_low = (int) pos.x / CHUNK_SIZE_X - RENDER_DISTANCE;
    z_low = (int) pos.z / CHUNK_SIZE_Z - RENDER_DISTANCE;
    x_high = x_low + RENDER_DISTANCE*2;
    z_high = z_low + RENDER_DISTANCE*2;
    InitializeChunks(pos);
}

void World::InitializeChunks(const glm::vec3& pos) {
    for (int i=x_low; i<=x_high; i++) {
        for (int k=z_low; k<=z_high; k++) {
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, -20, k*CHUNK_SIZE_Z);
            Chunk newChunk = Chunk(cpos, textureHandler);
            chunks.push_back(newChunk);
        }
    }
}

void World::UpdateChunks(const glm::vec3& pos) {
    int x_low_n = (int) pos.x / CHUNK_SIZE_X - RENDER_DISTANCE;
    int z_low_n = (int) pos.z / CHUNK_SIZE_Z - RENDER_DISTANCE;
    int x_high_n = x_low_n + RENDER_DISTANCE*2;
    int z_high_n = z_low_n + RENDER_DISTANCE*2;

    if (x_low_n < x_low) {
        AddChunks(x_low_n, x_low-1, z_low, z_high);
        RemoveChunks(x_high_n+1, x_high, z_low, z_high);
    } else if (x_high_n > x_high) {
        AddChunks(x_high+1, x_high_n, z_low, z_high);
        RemoveChunks(x_low, x_low_n-1, z_low, z_high);
    }
    x_low = x_low_n;
    x_high = x_high_n;

    if (z_low_n < z_low) {
        AddChunks(x_low, x_high, z_low_n, z_low-1);
        RemoveChunks(x_low, x_high, z_high_n+1, z_high);
    } else if (z_high_n > z_high) {
        AddChunks(x_low, x_high, z_high+1, z_high_n);
        RemoveChunks(x_low, x_high, z_low, z_low_n-1);
    }
    z_low = z_low_n;
    z_high = z_high_n;
}

void World::AddChunks(int xl, int xh, int zl, int zh) {
    for (int i=xl; i<=xh; i++) {
        for (int k=zl; k<=zh; k++) {
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, -20, k*CHUNK_SIZE_Z);
            Chunk newChunk = Chunk(cpos, textureHandler);
            chunks.push_back(newChunk);
        }
    }
}

void World::RemoveChunks(int xl, int xh, int zl, int zh) {
    chunks.erase(std::remove_if(chunks.begin(), chunks.end(), [xl, xh, zl, zh](Chunk& chunkx) {
        glm::vec3 pos {chunkx.GetPos()};
        pos.x /= CHUNK_SIZE_X;
        pos.z /= CHUNK_SIZE_Z;
        bool value = xl <= pos.x && pos.x <= xh && zl <= pos.z && pos.z <= zh;
        if (value) {
            chunkx.Delete();
        }
        return value;
    }), chunks.end());
}

void World::Render(Renderer& renderer) {
    for (Chunk& chunk: chunks) {
        renderer.RenderMesh(chunk.GetMesh().GetVAO(), chunk.GetMesh().GetVertexCount(), chunk.GetModel());
    }
}
