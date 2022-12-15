#include "Gui.h"
#include <GLFW/glfw3.h>

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

    int win_width = 0;
    int win_height = 0;
    glfwGetWindowSize(renderer.GetWindow(), &win_width, &win_height);
    float win_ratio = (float) win_width / (float) win_height;

    std::vector<float> crosshairVertices {};
    for (int i=0; i<6; i++) {
        for (int j=0; j<5; j++) {
            int value = squareVertices[i*5+j];
            if (j == 0) {
                crosshairVertices.push_back(value*(1.0f/24.0f));
            } else if (j == 1) {
                crosshairVertices.push_back(value*(1.0f/24.0f)*win_ratio);
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
