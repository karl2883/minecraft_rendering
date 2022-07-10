#include "ChunkMesh.h"

std::vector<float> cubeVertices = std::vector<float>({
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.70,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.70,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.70,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.70,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.70,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.70,

    -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.86,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.86,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.86,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.86,
    -0.5f,-0.5f, -0.5f,  0.0f, 0.0f, 0.86,
    -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.86,

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.86,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.86,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.86,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.86,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.86,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.86,

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.70,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.70,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.70,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.70,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.70,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.70,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f
});

void ChunkMesh::Clear() {
    vertices.clear();
}

void ChunkMesh::AddFace(const Block& block, const glm::vec3& pos, int side, TextureHandler& textureHandler) {
    std::vector<glm::vec2> coords = textureHandler.GetTextureCoordinates(block.GetBlockType(), side);

    for (int i=side*6; i<(side+1)*6; i++) {
        for (int j=0; j<3; j++) {
            vertices.push_back(cubeVertices[i*6+j]+pos[j]+0.5);
            if (block.GetBlockType() == BlockType::WATER && side == 0 && j == 1) {
                vertices[vertices.size()-1] -= 3.0f/16.0f;
            }
        }
        glm::vec2 vertexCoords;
        switch(i-(side*6)) {
            case 0: vertexCoords = coords[0]; break;
            case 1: vertexCoords = coords[2]; break;
            case 2: vertexCoords = coords[3]; break;
            case 3: vertexCoords = coords[3]; break;
            case 4: vertexCoords = coords[1]; break;
            case 5: vertexCoords = coords[0]; break;
        }
        vertices.push_back(vertexCoords[0]);
        vertices.push_back(vertexCoords[1]);
        // shading factor so you can differentiate the sides better
        vertices.push_back(cubeVertices[i*6+5]);
    }
}

void ChunkMesh::BuildMesh() {
    vbo = VertexBuffer(vertices.data(), vertices.size() * sizeof(float));
    VertexBufferLayout layout {};
    // coords
    layout.Push<float>(3);
    // texture coords
    layout.Push<float>(2);
    // shade factor
    layout.Push<float>(1);
    vao.AddBuffer(vbo, layout);
}

VertexArray& ChunkMesh::GetVAO() {
    return vao;
}

int ChunkMesh::GetVertexCount() const {
    return vertices.size() / 6;
}
