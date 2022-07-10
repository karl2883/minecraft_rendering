#include "Texture.h"

#include <GL/glew.h>
#include <iostream>
#include "stb_image.h"

Texture::Texture(const std::string& filepath, unsigned int format) { 
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int imwidth, imheight, nr_channels;
    unsigned char* data = stbi_load(filepath.c_str(), &imwidth, &imheight, &nr_channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imwidth, imheight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "Failed to load image!" << std::endl;
        stbi_image_free(data);
        return;
    }
}

Texture::Texture(const unsigned char* data, int imwidth, int imheight, unsigned int format) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imwidth, imheight, 0, format, GL_UNSIGNED_BYTE, data);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);  
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
