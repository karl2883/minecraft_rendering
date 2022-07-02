find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(World Chunk.cpp ChunkMesh.cpp Block.cpp World.cpp NoiseGenerator.cpp HeightMap.cpp ChunkGenerator.cpp Structure.cpp)
target_link_libraries(World glfw GLEW::GLEW OpenGL::GL)
