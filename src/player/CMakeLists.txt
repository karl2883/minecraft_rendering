add_library(Player Camera.cpp Player.cpp Ray.cpp)
target_link_libraries(Player glfw GLEW::GLEW OpenGL::GL)
