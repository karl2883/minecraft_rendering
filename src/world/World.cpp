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
        std::vector<Chunk> newVec {};
        for (int k=z_low; k<=z_high; k++) {
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, -20, k*CHUNK_SIZE_Z);
            Chunk newChunk = Chunk(cpos, textureHandler, this);
            newVec.push_back(newChunk);
        }
        chunks.push_back(newVec);
    }
    for (std::vector<Chunk>& vec: chunks) {
        for (Chunk& chunk: vec) {
            chunk.GenerateMesh(textureHandler);
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
    } else if (x_high_n > x_high) {
        AddChunks(x_high+1, x_high_n, z_low, z_high);
    }
    x_low = x_low_n;
    x_high = x_high_n;
    RemoveRedundantChunks();

    if (z_low_n < z_low) {
        AddChunks(x_low, x_high, z_low_n, z_low-1);
    } else if (z_high_n > z_high) {
        AddChunks(x_low, x_high, z_high+1, z_high_n);
    }
    z_low = z_low_n;
    z_high = z_high_n;
    RemoveRedundantChunks();
}

void World::AddChunks(int xl, int xh, int zl, int zh) {
    if (xl < x_low || xh > x_high) {
        AddChunksX(xl, xh);
    } else {
        AddChunksZ(zl, zh);
    }
}

void World::AddChunksX(int xl, int xh) {
    for (int i=xl; i<=xh; i++) {
        std::vector<Chunk> newVec {};
        // Adding the chunks
        for (int k=z_low; k<=z_high; k++) {
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, -20, k*CHUNK_SIZE_Z);
            Chunk newChunk = Chunk(cpos, textureHandler, this);
            newChunk.GenerateMesh(textureHandler);
            newVec.push_back(newChunk);
        }
        // adding to 2d chunk list and redo meshes (adjacent chunks too)
        if (i < x_low) {
            chunks.insert(chunks.begin(), newVec);
            for (int x=i; x<=x_low; x++) {
                for (int z=z_low; z<=z_high; z++) {
                    chunks[x-i][z-z_low].GenerateMesh(textureHandler);
                }
            }
        } else {
            chunks.push_back(newVec);
            for (int x=x_high; x<=i; x++) {
                for (int z=z_low; z<=z_high; z++) {
                    chunks[x-x_low][z-z_low].GenerateMesh(textureHandler);
                }
            }
        }
    }
}

void World::AddChunksZ(int zl, int zh) {
    // Adding the chunks
    for (int i=x_low; i<=x_high; i++) {
        std::vector<Chunk>& vec = chunks[i-x_low];
        for (int k=zl; k<=zh; k++) {
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, -20, k*CHUNK_SIZE_Z);
            Chunk newChunk = Chunk(cpos, textureHandler, this);
            if (k < z_low) {
                vec.insert(vec.begin(), newChunk);
            }
            else {
                vec.push_back(newChunk);
            }
        }
    }
    // redo meshes (adjacent chunks too)
    if (zl < z_low) {
        for (int x=x_low; x<=x_high; x++) {
            for (int z=zl; z<=z_low; z++) {
                chunks[x-x_low][z-zl].GenerateMesh(textureHandler);
            }
        }
    } else {
        for (int x=x_low; x<=x_high; x++) {
            for (int z=z_high; z<=zh; z++) {
                chunks[x-x_low][z-z_low].GenerateMesh(textureHandler);
            }
        }
    }
}

void World::RemoveRedundantChunks() {
    if (chunks[0][0].GetPos().x / CHUNK_SIZE_X < x_low) {
        chunks.erase(chunks.begin());
        for (Chunk& chunk: chunks[0]) {
            chunk.GenerateMesh(textureHandler);
        }
    }
    if (chunks.back()[0].GetPos().x / CHUNK_SIZE_X > x_high) {
        chunks.pop_back();
        for (Chunk& chunk: chunks.back()) {
            chunk.GenerateMesh(textureHandler);
        }
    }
    
    if (chunks[0][0].GetPos().z / CHUNK_SIZE_Z < z_low) {
        for (std::vector<Chunk>& vec: chunks) {
            vec.erase(vec.begin());
            vec[0].GenerateMesh(textureHandler);
        }
    }
    if (chunks[0].back().GetPos().z / CHUNK_SIZE_Z > z_high) {
        for (std::vector<Chunk>& vec: chunks) {
            vec.pop_back();
            vec.back().GenerateMesh(textureHandler);
        }
    }
}

void World::Render(Renderer& renderer) {
    for (std::vector<Chunk>& vec: chunks) {
        for (Chunk& chunk: vec) {
            renderer.RenderMesh(chunk.GetMesh().GetVAO(), chunk.GetMesh().GetVertexCount(), chunk.GetModel());
        }
    }
}

bool World::BlockInBounds(const glm::vec3 &pos) {
    int bx = (int)pos.x % CHUNK_SIZE_X;
    if (bx < 0) bx += CHUNK_SIZE_X;
    int bz = (int)pos.z % CHUNK_SIZE_Z;
    if (bz < 0) bz += CHUNK_SIZE_Z;
    int cx = pos.x - bx;
    int cz = pos.z - bz;
    for (std::vector<Chunk>& vec: chunks) {
        for (Chunk& chunk: vec) {
            glm::vec3& cpos = chunk.GetPos(); 
            if (cpos.x == cx && cpos.z == cz) {
                return true; 
            }
        }
    }
    return false;
}

Block& World::GetBlock(const glm::vec3 &pos) {
    int bx = (int)pos.x % CHUNK_SIZE_X;
    if (bx < 0) bx += CHUNK_SIZE_X;
    int bz = (int)pos.z % CHUNK_SIZE_Z;
    if (bz < 0) bz += CHUNK_SIZE_Z;
    int cx = pos.x - bx;
    int cz = pos.z - bz;
    for (std::vector<Chunk>& vec: chunks) {
        for (Chunk& chunk: vec) {
            glm::vec3& cpos = chunk.GetPos(); 
            if (cpos.x == cx && cpos.z == cz) {
                return chunk.GetBlock(bx, pos.y+20, bz);
            }
        }
    }
    throw "No Block found, forgot to use BlockInBounds";
}
