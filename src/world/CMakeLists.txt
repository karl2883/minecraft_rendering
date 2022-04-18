find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(World Chunk.cpp ChunkMesh.cpp Block.cpp)
