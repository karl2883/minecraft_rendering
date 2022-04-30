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
    x_low_old = x_low;
    x_high_old = x_high;
    z_low_old = z_low;
    z_high_old = z_high; 

    x_low = (int) pos.x / CHUNK_SIZE_X - RENDER_DISTANCE;
    z_low = (int) pos.z / CHUNK_SIZE_Z - RENDER_DISTANCE;
    x_high = x_low + RENDER_DISTANCE*2;
    z_high = z_low + RENDER_DISTANCE*2;

    // avoid updating in both x and z direction at the same time
    if (x_low != x_low_old && z_low != z_low_old) {
        z_low = z_low_old;
        z_high = z_high_old;
    }

    RemoveRedundantChunks();

    if (x_low < x_low_old) {
        AddChunksX(x_low);
    } else if (x_high > x_high_old) {
        AddChunksX(x_high);
    }

    if (z_low < z_low_old) {
        AddChunksZ(z_low);
    } else if (z_high > z_high_old) {
        AddChunksZ(z_high);
    }
}

void World::AddChunksX(int xn) {
    std::vector<Chunk> newVec {};
    // Adding the chunks
    for (int k=z_low; k<=z_high; k++) {
        glm::vec3 cpos = glm::vec3(xn*CHUNK_SIZE_X, -20, k*CHUNK_SIZE_Z);
        Chunk newChunk = Chunk(cpos, textureHandler, this);
        newVec.push_back(newChunk);
    }
    // adding to 2d chunk list and redo meshes (adjacent chunks too)
    if (xn < x_low_old) {
        chunks.insert(chunks.begin(), newVec);
        for (int x=xn; x<=x_low_old; x++) {
            for (int z=z_low; z<=z_high; z++) {
                chunks[x-x_low][z-z_low].GenerateMesh(textureHandler);
            }
        }
    } else {
        chunks.push_back(newVec);
        for (int x=x_high_old; x<=xn; x++) {
            for (int z=z_low; z<=z_high; z++) {
                chunks[x-x_low][z-z_low].GenerateMesh(textureHandler);
            }
        }
    }
}

void World::AddChunksZ(int zn) {
    // Adding the chunks
    for (int i=x_low; i<=x_high; i++) {
        std::vector<Chunk>& vec = chunks[i-x_low];
        glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, -20, zn*CHUNK_SIZE_Z);
        Chunk newChunk = Chunk(cpos, textureHandler, this);
        if (zn < z_low_old) {
            vec.insert(vec.begin(), newChunk);
        }
        else {
            vec.push_back(newChunk);
        }
    }
    // redo meshes (adjacent chunks too)
    if (zn < z_low_old) {
        for (int x=x_low; x<=x_high; x++) {
            for (int z=zn; z<=z_low_old; z++) {
                chunks[x-x_low][z-z_low].GenerateMesh(textureHandler);
            }
        }
    } else {
        for (int x=x_low; x<=x_high; x++) {
            for (int z=z_high_old; z<=zn; z++) {
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
    return (x_low*CHUNK_SIZE_X <= pos.x && pos.x < (x_high+1)*CHUNK_SIZE_X &&
            z_low*CHUNK_SIZE_Z <= pos.z && pos.z < (z_high+1)*CHUNK_SIZE_Z);
}

Block& World::GetBlock(const glm::vec3 &pos) {
    int bx = (int)pos.x % CHUNK_SIZE_X;
    if (bx < 0) bx += CHUNK_SIZE_X;
    int bz = (int)pos.z % CHUNK_SIZE_Z;
    if (bz < 0) bz += CHUNK_SIZE_Z;

    int cx = (pos.x - bx) / CHUNK_SIZE_X;
    int cz = (pos.z - bz) / CHUNK_SIZE_Z;

    Chunk& chunk = chunks[cx-x_low][cz-z_low];
    return chunk.GetBlock(bx, pos.y+20, bz);
}
