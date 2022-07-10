#pragma once

class Texture {
private:
    unsigned int ID;
public:
    Texture() {}
    Texture(const unsigned char* data, int imwidth, int imheigth, unsigned int format);
    void Bind() const;
    void Unbind() const;
};

