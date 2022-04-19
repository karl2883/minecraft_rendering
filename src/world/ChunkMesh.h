#pragma once

#include "Block.h"
#include "../gfx/TextureHandler.h"
#include "../model/VertexArray.h"
#include "../model/VertexBufferLayout.h"
#include "../model/VertexBuffer.h"

#include <glm/glm.hpp>

class ChunkMesh {
private:
    std::vector<float> vertices;
    VertexBuffer vbo;
    VertexArray vao;
public:
    ChunkMesh(TextureHandler& textureHandler) {}
    
    void AddFace(const Block& block, const glm::vec3& pos, int side, TextureHandler& textureHandler);
    void BuildMesh();
    VertexArray& GetVAO();
    int GetVertexCount() const;
};
