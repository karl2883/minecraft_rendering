#include "World.h"
#include <glm/gtx/io.hpp>

using namespace WorldConstants;

World::World(const glm::vec3& pos, TextureHandler& textureHandler) 
:textureHandler(textureHandler), noiseGenerator(2883)
{
    srand(noiseGenerator.GetSeed());

    x_low = (int) pos.x / CHUNK_SIZE_XZ - RENDER_DISTANCE;
    z_low = (int) pos.z / CHUNK_SIZE_XZ - RENDER_DISTANCE;
    x_high = x_low + RENDER_DISTANCE*2;
    z_high = z_low + RENDER_DISTANCE*2;
    InitializeChunks(pos);
}

void World::InitializeChunks(const glm::vec3& pos) {
    for (int i=x_low; i<=x_high; i++) {
        std::vector<Chunk> newVec {};
        for (int k=z_low; k<=z_high; k++) {
            glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_XZ, Y_OFFSET, k*CHUNK_SIZE_XZ);
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

// updating chunks depending on the player position,
// also generate the one mesh per frame
void World::UpdateChunks(const glm::vec3& pos) {
    x_low_old = x_low;
    x_high_old = x_high;
    z_low_old = z_low;
    z_high_old = z_high; 

    // determine new bounds for the loaded chunks depending on the player position
    x_low = (int) pos.x / CHUNK_SIZE_XZ - RENDER_DISTANCE;
    z_low = (int) pos.z / CHUNK_SIZE_XZ - RENDER_DISTANCE;
    x_high = x_low + RENDER_DISTANCE*2;
    z_high = z_low + RENDER_DISTANCE*2;

    // avoid updating in both x and z direction at the same time
    if (x_low != x_low_old && z_low != z_low_old) {
        z_low = z_low_old;
        z_high = z_high_old;
    }

    // first remove chunks outside of the range
    RemoveRedundantChunks();

    // then add chunks
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
    // don't generate chunks that are not in bounds
    while (!mesh_generation_queue.empty() && !ChunkInBounds(mesh_generation_queue.front())) {
        mesh_generation_queue.pop();
    }
    if (!mesh_generation_queue.empty()) {
        glm::vec2& generated_mesh_pos = mesh_generation_queue.front();
        chunks[generated_mesh_pos.x-x_low][generated_mesh_pos.y-z_low].GenerateMesh(textureHandler);
        mesh_generation_queue.pop();
    }
}

// add a row of chunks in x direction where xn is the x position of the row
void World::AddChunksX(int xn) {
    std::vector<Chunk> newVec {};
    // Adding the chunks
    for (int k=z_low; k<=z_high; k++) {
        glm::vec3 cpos = glm::vec3(xn*CHUNK_SIZE_XZ, Y_OFFSET, k*CHUNK_SIZE_XZ);
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

// add a row of chunks in z direction where zn is the z position of the row
void World::AddChunksZ(int zn) {
    // Adding the chunks
    for (int i=x_low; i<=x_high; i++) {
        std::vector<Chunk>& vec = chunks[i-x_low];
        glm::vec3 cpos = glm::vec3(i*CHUNK_SIZE_XZ, Y_OFFSET, zn*CHUNK_SIZE_XZ);
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

// remove all chunks which are outside of the x-low to x-high and z-low to z-high range,
// using the queue
void World::RemoveRedundantChunks() {
    if (chunks[0][0].GetPos().x / CHUNK_SIZE_XZ < x_low) {
        chunks.erase(chunks.begin());
        for (Chunk& chunk: chunks[0]) {
            mesh_generation_queue.push(GetChunkPos(chunk));
        }
    }
    if (chunks.back()[0].GetPos().x / CHUNK_SIZE_XZ > x_high) {
        chunks.pop_back();
        for (Chunk& chunk: chunks.back()) {
            mesh_generation_queue.push(GetChunkPos(chunk));
        }
    }
    
    if (chunks[0][0].GetPos().z / CHUNK_SIZE_XZ < z_low) {
        for (std::vector<Chunk>& vec: chunks) {
            vec.erase(vec.begin());
            mesh_generation_queue.push(GetChunkPos(vec[0]));
        }
    }
    if (chunks[0].back().GetPos().z / CHUNK_SIZE_XZ > z_high) {
        for (std::vector<Chunk>& vec: chunks) {
            vec.pop_back();
            mesh_generation_queue.push(GetChunkPos(vec.back()));
        }
    }
}

void World::Render(Renderer& renderer) {
    for (std::vector<Chunk>& vec: chunks) {
        for (Chunk& chunk: vec) {
            // it can happen that the mesh isn't generated because with the queue only one mesh generates per frame
            // in that case the program would crash when you try to render, so check before
            if (chunk.MeshGenerated()) {
                renderer.RenderMesh(chunk.GetMesh().GetVAO(), chunk.GetMesh().GetVertexCount(), chunk.GetModel());
            }
        }
    }
}

// self-explanatory
bool World::BlockInBounds(const glm::vec3& pos) {
    return (x_low*CHUNK_SIZE_XZ <= pos.x && pos.x < (x_high+1)*CHUNK_SIZE_XZ &&
            z_low*CHUNK_SIZE_XZ <= pos.z && pos.z < (z_high+1)*CHUNK_SIZE_XZ &&
            Y_OFFSET <= pos.y && pos.y < Y_OFFSET+CHUNK_SIZE_Y);
}

// self-explanatory, uses world-chunk-coordinates for x and z, e.g. 1 1 instead of 16 16
bool World::ChunkInBounds(const glm::vec2& pos) {
    return (x_low <= pos.x && x_high >= pos.x && z_low <= pos.y && z_high >= pos.y);
}

// sets a block at the pos, meshes get updated automatically, including neighbour meshes that are affected
void World::SetBlock(glm::vec3 pos, BlockType newBlockType) {
    Block& block = GetBlock(pos);
    block.SetBlockType(newBlockType);
    Chunk& chunk = GetChunk(pos);
    // the meshes are generated immediately here because there are maximal 3 meshes that get regenerated (when the block is on a corner)
    // and everything else would look weird probably
    // that means not using the queue here
    chunk.GenerateMesh(textureHandler);

    glm::vec3 blockCoords = GetBlockCoordinates(pos);
    // a list of the offsets to all affected neighbour chunks
    std::vector<glm::vec2> offsets = chunk.GetNeighbourChunkOffsets(blockCoords.x, blockCoords.y, blockCoords.z);
    for (glm::vec2& offset: offsets) {
        glm::vec3 newpos = glm::vec3(pos.x+offset.x, pos.y, pos.z+offset.y);
        if (BlockInBounds(newpos)) {
            GetChunk(newpos).GenerateMesh(textureHandler);
        }
    }
}

// returns the block-coordinates in the pos, the block-coordinates are relative to the 0,0,0-edge of the chunk the block is in
glm::vec3 World::GetBlockCoordinates(glm::vec3& pos) {
    int bx = (int)pos.x % CHUNK_SIZE_XZ;
    if (bx < 0) bx += CHUNK_SIZE_XZ;
    int bz = (int)pos.z % CHUNK_SIZE_XZ;
    if (bz < 0) bz += CHUNK_SIZE_XZ;

    return glm::vec3(bx, (int)pos.y-Y_OFFSET, bz);
}

// returns a two-dimensional vector with the x and z coordinates of the chunk the pos is in, the coordinates are world-chunk-coordinates, that means e.g. 1 1 instead of 16 16
glm::vec2 World::GetChunkPos(glm::vec3& pos) {
    // a bit clunky but eh
    glm::vec3 blockCoords = GetBlockCoordinates(pos);

    int cx = (pos.x - blockCoords.x) / CHUNK_SIZE_XZ;
    int cz = (pos.z - blockCoords.z) / CHUNK_SIZE_XZ;

    return glm::vec2(cx, cz);
}

// returns a two-dimensional vector with the x and z coordinates of the chunk, the coordinates are world-chunk-coordinates, that means e.g. 1 1 instead of 16 16
glm::vec2 World::GetChunkPos(Chunk& chunk) {
    return GetChunkPos(chunk.GetPos());
}

// returns the chunk the pos is in
Chunk& World::GetChunk(glm::vec3& pos) {
    glm::vec3 blockCoords = GetBlockCoordinates(pos);

    int cx = (pos.x - blockCoords.x) / CHUNK_SIZE_XZ;
    int cz = (pos.z - blockCoords.z) / CHUNK_SIZE_XZ;
    
    Chunk& chunk = chunks[cx-x_low][cz-z_low];
    return chunk;
}

// returns the block at the given pos
Block& World::GetBlock(glm::vec3 &pos) {
    glm::vec3 blockCoords = GetBlockCoordinates(pos);
    Chunk& chunk = GetChunk(pos);
    return chunk.GetBlock(blockCoords.x, blockCoords.y, blockCoords.z);
}
