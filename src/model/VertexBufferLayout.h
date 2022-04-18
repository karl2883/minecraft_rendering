#pragma once

#include <vector>
#include <GL/glew.h>
#include <iostream>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VertexBufferLayout 
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {}

    template<typename T> void Push(unsigned int count);

    inline const std::vector<VertexBufferElement> getElements() const& {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
};

template<> inline void VertexBufferLayout::Push<float>(unsigned int count) {
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
};

template<> inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
};

template<> inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
};
