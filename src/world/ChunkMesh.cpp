#include "ChunkMesh.h"

std::vector<float> cubeVertices = std::vector<float>({
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

    0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,-0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f
});

void ChunkMesh::AddFace(const Block& block, const glm::vec3& pos, int side) {
    std::vector<glm::vec2> coords = textureHandler.GetSideCoordinates(side);

    for (int i=side*6; i<(side+1)*6; i++) {
        for (int j=0; j<3; j++) {
            vertices.push_back(cubeVertices[i*5+j]+pos[j]+0.5);
        }
        glm::vec2 vertexCoords;
        switch(i-(side*6)) {
            case 0: vertexCoords = coords[0]; break;
            case 1: vertexCoords = coords[2]; break;
            case 2: vertexCoords = coords[3]; break;
            case 3: vertexCoords = coords[3]; break;
            case 4: vertexCoords = coords[1]; break;
            case 5: vertexCoords = coords[0]; break;
            default: std::cout << "what" << std::endl;
        }
        vertices.push_back(vertexCoords[0]);
        vertices.push_back(vertexCoords[1]);
    }
}

void ChunkMesh::BuildMesh() {
    vbo = VertexBuffer(vertices.data(), vertices.size() * sizeof(float));
    VertexBufferLayout layout {};
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);
}

VertexArray& ChunkMesh::GetVAO() {
    return vao;
}

int ChunkMesh::GetVertexCount() const {
    return vertices.size() / 5;
}

void ChunkMesh::Reset() {
    faces.clear();
}
