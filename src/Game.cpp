#include "Game.h"

void Game::MouseCallback(const GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) // initially set to true
    {
        lastx = xpos;
        lasty = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; // reversed since y-coordinates range from bottom to top
    lastx = xpos;
    lasty = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.Rotate(YAW, xoffset);
    camera.Rotate(PITCH, yoffset);
}

void Game::ProcessInput(GLFWwindow* window) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        visibility += 0.001f;
    } 
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        visibility -= 0.001f;
    }

    if (glfwGetKey(window, GLFW_KEY_L)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_F)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    const float cameraSpeed = 10.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.Move(FORWARDS, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.Move(BACKWARDS, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.Move(LEFT, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.Move(RIGHT, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.Move(UP, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.Move(DOWN, cameraSpeed);
    }
}

bool Game::ShouldRun() const {
    return !glfwWindowShouldClose(window);
}

void Game::UpdateEvents() {
    glfwPollEvents();
}

Game::Game(GLFWwindow* win) 
    // sorry for hardcoded paths
    :shader("src/gfx/Shaders/VertexShader.vs", "src/gfx/Shaders/FragmentShader.fs"),
    camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
    textureHandler((char*)"pixelartattempt/grass.png"),
    renderer(win, shader, camera, 800, 600, 45.0f, textureHandler),
    world(glm::vec3(0.0f, 0.0f, 3.0f), textureHandler)
{
    glfwSetWindowUserPointer(win, this);

    visibility = 0.2f;
    width = 800;
    height = 600;

    deltaTime = 0.0f;
    lastFrame = 0.0f;

    // Keep track of whether we have an initial position for the mouse or not
    firstMouse = true;

    // reference variables for the mouse
    lastx = 400, lastx = 300;

    window = win;

    // Alter between GL_LINE (for wireframe) and GL_FILL (normal)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::Run() {
    
    int frameCount = 0;
    float timeSum = 0.0f;

    while (ShouldRun()) {
        UpdateEvents();
        ProcessInput(window);

        world.UpdateChunks(camera.GetPos());
        // output how much fps we have
        timeSum += deltaTime;
        frameCount++;
        if (frameCount == 120) {
            std::cout << 1.0f / (timeSum / 120.0f) << " FPS"<< std::endl;
            frameCount = 0;
            timeSum = 0.0f;
        }

        // Rendering
        renderer.Clear();
        renderer.UpdateView();

        world.Render(renderer);

        renderer.Update();
    }

    glfwTerminate();
}
