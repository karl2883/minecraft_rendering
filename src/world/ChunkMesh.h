#pragma once

#include "Block.h"
#include "../gfx/TextureHandler.h"
#include "../model/VertexArray.h"
#include "../model/VertexBufferLayout.h"
#include "../model/VertexBuffer.h"

#include <glm/glm.hpp>

struct Face {
    Block& block;
    int side;
};

class ChunkMesh {
private:
    std::vector<Face> faces;
    std::vector<float> vertices;
    TextureHandler& textureHandler;
    VertexBuffer vbo;
    VertexArray vao;
public:
    ChunkMesh(TextureHandler& textureHandler) :textureHandler(textureHandler) {}
    
    void AddFace(const Block& block, const glm::vec3& pos, int side);
    void BuildMesh();
    void Reset();
    VertexArray& GetVAO();
    int GetVertexCount() const;
};
