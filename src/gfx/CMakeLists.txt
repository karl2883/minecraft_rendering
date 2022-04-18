find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(Gfx Shader.cpp Renderer.cpp Texture.cpp TextureHandler.cpp)
