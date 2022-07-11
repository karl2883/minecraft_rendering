#include "Gui.h"

std::vector<float> squareVertices = {
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f
}; 

GUI::GUI(Renderer& renderer)
:renderer(renderer), crosshairModel(1.0f)
{
    int nr_channels;
    int width;
    int height;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load("pixelartattempt/crosshair.png", &width, &height, &nr_channels, 0);

    crosshairTexture = Texture{data, width, height, GL_RGBA};

    std::vector<float> crosshairVertices {};
    for (int i=0; i<6; i++) {
        for (int j=0; j<5; j++) {
            int value = squareVertices[i*5+j];
            if (j < 2) {
                crosshairVertices.push_back(value*(1.0f/24.0f));
            } else {
                crosshairVertices.push_back(value);
            }
        }
    }

    VertexBuffer squareBuffer {crosshairVertices.data(), static_cast<int>(squareVertices.size() * sizeof(float))};
    VertexBufferLayout layout {};
    layout.Push<float>(3);
    layout.Push<float>(2);
    squareVAO.AddBuffer(squareBuffer, layout);
}

void GUI::Render() {
    renderer.RenderGUIMesh(crosshairTexture, squareVAO, 6, crosshairModel);
}
