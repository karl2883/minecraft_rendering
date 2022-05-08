#include "World.h"
#include <glm/gtx/io.hpp>

World::World(const glm::vec3& pos, TextureHandler& textureHandler) 
:textureHandler(textureHandler), noiseGenerator(2883)
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
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, Y_OFFSET, k*CHUNK_SIZE_Z);
            Chunk newChunk = Chunk(cpos, textureHandler, noiseGenerator, this);
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

    // generate meshes for one chunk per frame (for smoothness)
    while (!mesh_generation_queue.empty() && !ChunkInBounds(mesh_generation_queue.front())) {
        mesh_generation_queue.pop();
    }
    if (!mesh_generation_queue.empty()) {
        glm::vec2& generated_mesh_pos = mesh_generation_queue.front();
        chunks[generated_mesh_pos.x-x_low][generated_mesh_pos.y-z_low].GenerateMesh(textureHandler);
        mesh_generation_queue.pop();
    }
}

void World::AddChunksX(int xn) {
    std::vector<Chunk> newVec {};
    // Adding the chunks
    for (int k=z_low; k<=z_high; k++) {
        glm::vec3 cpos = glm::vec3(xn*CHUNK_SIZE_X, Y_OFFSET, k*CHUNK_SIZE_Z);
        Chunk newChunk = Chunk(cpos, textureHandler, noiseGenerator, this);
        newVec.push_back(newChunk);
    }
    // adding to 2d chunk list and redo meshes (adjacent chunks too)
    if (xn < x_low_old) {
        chunks.insert(chunks.begin(), newVec);
        for (int x=xn; x<=x_low_old; x++) {
            for (int z=z_low; z<=z_high; z++) {
                mesh_generation_queue.push(glm::vec2(x, z));
            }
        }
    } else {
        chunks.push_back(newVec);
        for (int x=x_high_old; x<=xn; x++) {
            for (int z=z_low; z<=z_high; z++) {
                mesh_generation_queue.push(glm::vec2(x, z));
            }
        }
    }
}

void World::AddChunksZ(int zn) {
    // Adding the chunks
    for (int i=x_low; i<=x_high; i++) {
        std::vector<Chunk>& vec = chunks[i-x_low];
        glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_X, Y_OFFSET, zn*CHUNK_SIZE_Z);
        Chunk newChunk = Chunk(cpos, textureHandler, noiseGenerator, this);
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
                mesh_generation_queue.push(glm::vec2(x, z));
            }
        }
    } else {
        for (int x=x_low; x<=x_high; x++) {
            for (int z=z_high_old; z<=zn; z++) {
                mesh_generation_queue.push(glm::vec2(x, z));
            }
        }
    }
}

void World::RemoveRedundantChunks() {
    if (chunks[0][0].GetPos().x / CHUNK_SIZE_X < x_low) {
        chunks.erase(chunks.begin());
        for (Chunk& chunk: chunks[0]) {
            mesh_generation_queue.push(GetChunkPos(chunk));
        }
    }
    if (chunks.back()[0].GetPos().x / CHUNK_SIZE_X > x_high) {
        chunks.pop_back();
        for (Chunk& chunk: chunks.back()) {
            mesh_generation_queue.push(GetChunkPos(chunk));
        }
    }
    
    if (chunks[0][0].GetPos().z / CHUNK_SIZE_Z < z_low) {
        for (std::vector<Chunk>& vec: chunks) {
            vec.erase(vec.begin());
            mesh_generation_queue.push(GetChunkPos(vec[0]));
        }
    }
    if (chunks[0].back().GetPos().z / CHUNK_SIZE_Z > z_high) {
        for (std::vector<Chunk>& vec: chunks) {
            vec.pop_back();
            mesh_generation_queue.push(GetChunkPos(vec.back()));
        }
    }
}

void World::Render(Renderer& renderer) {
    for (std::vector<Chunk>& vec: chunks) {
        for (Chunk& chunk: vec) {
            if (chunk.MeshGenerated()) {
                renderer.RenderMesh(chunk.GetMesh().GetVAO(), chunk.GetMesh().GetVertexCount(), chunk.GetModel());
            }
        }
    }
}

bool World::BlockInBounds(const glm::vec3 &pos) {
    return (x_low*CHUNK_SIZE_X <= pos.x && pos.x < (x_high+1)*CHUNK_SIZE_X &&
            z_low*CHUNK_SIZE_Z <= pos.z && pos.z < (z_high+1)*CHUNK_SIZE_Z &&
            Y_OFFSET <= pos.y && pos.y < Y_OFFSET+CHUNK_SIZE_Y);
}

bool World::ChunkInBounds(const glm::vec2& pos) {
    return (x_low <= pos.x && x_high >= pos.x && z_low <= pos.y && z_high >= pos.y);
}

void World::SetBlock(glm::vec3 pos, BlockType newBlockType) {
    Block& block = GetBlock(pos);
    block.SetBlockType(newBlockType);
    Chunk& chunk = GetChunk(pos);
    chunk.GenerateMesh(textureHandler);

    glm::vec3 blockCoords = GetBlockCoordinates(pos);
    std::vector<glm::vec2> offsets = chunk.GetNeighbourChunkOffsets(blockCoords.x, blockCoords.y, blockCoords.z);
    for (glm::vec2& offset: offsets) {
        glm::vec3 newpos = glm::vec3(pos.x+offset.x, pos.y, pos.z+offset.y);
        if (BlockInBounds(newpos)) {
            GetChunk(newpos).GenerateMesh(textureHandler);
        }
    }
}

glm::vec3 World::GetBlockCoordinates(glm::vec3& pos) {
    int bx = (int)pos.x % CHUNK_SIZE_X;
    if (bx < 0) bx += CHUNK_SIZE_X;
    int bz = (int)pos.z % CHUNK_SIZE_Z;
    if (bz < 0) bz += CHUNK_SIZE_Z;

    return glm::vec3(bx, (int)pos.y-Y_OFFSET, bz);
}

glm::vec2 World::GetChunkPos(Chunk& chunk) {
    glm::vec3& p = chunk.GetPos();
    glm::vec3 blockCoords = GetBlockCoordinates(p);

    int cx = (p.x - blockCoords.x) / CHUNK_SIZE_X;
    int cz = (p.z - blockCoords.z) / CHUNK_SIZE_Z;
    return glm::vec2(cx, cz);
}

Chunk& World::GetChunk(glm::vec3& pos) {
    glm::vec3 blockCoords = GetBlockCoordinates(pos);

    int cx = (pos.x - blockCoords.x) / CHUNK_SIZE_X;
    int cz = (pos.z - blockCoords.z) / CHUNK_SIZE_Z;
    
    Chunk& chunk = chunks[cx-x_low][cz-z_low];
    return chunk;
}

Block& World::GetBlock(glm::vec3 &pos) {
    glm::vec3 blockCoords = GetBlockCoordinates(pos);
    Chunk& chunk = GetChunk(pos);
    return chunk.GetBlock(blockCoords.x, blockCoords.y, blockCoords.z);
}
