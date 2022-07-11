#include "Renderer.h"
#include <chrono>

// paramenters with "n" at the start to avoid "width = width;"
Renderer::Renderer(GLFWwindow* newwindow, Camera& camera, int nwidth, int nheight, float nfov, TextureHandler& textureHandler)
    :camera(camera),
    shader("src/gfx/Shaders/VertexShader.vs", "src/gfx/Shaders/FragmentShader.fs"),
    guiShader("src/gfx/Shaders/VertexShaderGUI.vs", "src/gfx/Shaders/FragmentShaderGUI.fs"),
    textureHandler(textureHandler)
{
    window = newwindow;

    width = nwidth;
    height = nheight;
    fov = nfov;

    UpdateProjection();
    UpdateView();
}

void Renderer::ChangeFov(float newfov) {
    fov = newfov;
    UpdateProjection();
}

void Renderer::Resize(int newwidth, int newheight) {
    width = newwidth;
    height = newheight;
    UpdateProjection();
}

void Renderer::SetShader(const Shader& nshader) {
    shader = nshader;
}

// you pretty much have to call this every frame since the mouse will often move every frame
void Renderer::UpdateView() {
    view = camera.GetViewMatrix();
    VP = projection * view;
}

void Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearDepthBuffer() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderMesh(const VertexArray& vao, int verticeCount, const glm::mat4& model) {
    // vao is the model out of vertices
    // model is the model transformation matrix
    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("FogStart", WorldConstants::FOG_START);
    shader.SetInt("FogEnd", WorldConstants::FOG_END);
    shader.SetMat4("MVP", VP * model);
    shader.SetMat4("MV", view * model);
    glActiveTexture(GL_TEXTURE0);
    vao.Bind();
    textureHandler.GetTexture().Bind();

    glDrawArrays(GL_TRIANGLES, 0, verticeCount);
}

void Renderer::RenderGUIMesh(Texture& texture, const VertexArray& vao, int verticeCount, const glm::mat4& model) {
    guiShader.Use();
    guiShader.SetInt("texture1", 0);
    guiShader.SetMat4("M", model);
    glActiveTexture(GL_TEXTURE0);
    vao.Bind();
    texture.Bind();

    glDrawArrays(GL_TRIANGLES, 0, verticeCount);
}

void Renderer::Update() {
    glfwSwapBuffers(window);
}

// you only call this function when something changes to avoid unnecessary calculations
void Renderer::UpdateProjection() {
    projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 2000.0f);
    VP = projection * view;
}
