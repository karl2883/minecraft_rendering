#pragma once

#include "Shader.h"
#include "TextureHandler.h"
#include "../world/Constants.h"
#include "../model/VertexArray.h"
#include "../player/Camera.h"
#include "Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer {
private:
    int width;
    int height;
    // e.g. 45°
    float fov;

    Shader& shader;

    Camera& camera;

    GLFWwindow* window;

    TextureHandler& textureHandler;

    // last matrix used for projecting onto 2d screen with -1 to 1 coordinates
    glm::mat4 projection;
    // camera matrix to transform 3d space to the pov of the camera
    glm::mat4 view;
    // combination of both that only gets calculated once (or twice) per frame on the cpu to save computing power
    glm::mat4 VP;

    void UpdateProjection();
public:
    Renderer(GLFWwindow* window, Shader& shader, Camera& camera, int width, int height, float fov, TextureHandler& textureHandler);

    void SetShader(const Shader& shader);
    void Resize(int width, int height);
    void ChangeFov(float newfov);

    void UpdateView();

    void Clear();
    void RenderMesh(const VertexArray& vao, int verticeCount, const glm::mat4& model);
    void Update();

    TextureHandler& GetTextureHandler() const { return textureHandler; }
};
