#pragma once

#include <string>

class Texture {
private:
    unsigned int ID;
public:
    Texture() {}
    Texture(const std::string& filepath, unsigned int format);
    Texture(const unsigned char* data, int imwidth, int imheigth, unsigned int format);
    void Bind() const;
    void Unbind() const;
};

