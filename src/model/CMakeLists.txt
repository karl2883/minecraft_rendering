find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(Model VertexBuffer.cpp VertexArray.cpp)
target_link_libraries(Model glfw GLEW::GLEW OpenGL::GL)
