#pragma once

class VertexBuffer {
private:
    unsigned int ID;
public:
    VertexBuffer() {};
    VertexBuffer(const void* data, int size);
    void Bind() const;
};
