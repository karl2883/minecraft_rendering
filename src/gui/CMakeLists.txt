find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(GUI Gui.cpp)
target_link_libraries(GUI GLEW::GLEW OpenGL::GL)
