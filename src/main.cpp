#include "Core/Window.h"
#include "Core/Shader.h"
#include "Core/Camera.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

float lastX = 400, lastY = 300;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    Core::Camera* camera = static_cast<Core::Camera*>(glfwGetWindowUserPointer(window));
    camera->rotate(xoffset, yoffset);
}

int main(int argc, char** argv) {
    Core::Window window(800, 600, "Sunshine");
    
    if (!window.init()) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    fs::path exePath = fs::absolute(fs::path(argv[0]));
    fs::path shaderDir = exePath.parent_path() / "shaders";

    Core::Shader shader((shaderDir / "vertex.glsl").string().c_str(), 
                        (shaderDir / "fragment.glsl").string().c_str());
    if (!shader.isValid()) {
        std::cerr << "Failed to create shader program" << std::endl;
        return -1;
    }

    Core::Camera camera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    glfwSetWindowUserPointer(window.getGLFWwindow(), &camera);
    glfwSetCursorPosCallback(window.getGLFWwindow(), mouse_callback);
    glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!window.shouldClose()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        float cameraSpeed = 0.05f;
        if (glfwGetKey(window.getGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() + cameraSpeed * camera.getTarget());
        if (glfwGetKey(window.getGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() - cameraSpeed * camera.getTarget());
        if (glfwGetKey(window.getGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() - glm::normalize(glm::cross(camera.getTarget(), camera.getUp())) * cameraSpeed);
        if (glfwGetKey(window.getGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() + glm::normalize(glm::cross(camera.getTarget(), camera.getUp())) * cameraSpeed);

        // Set the view and projection matrices in the shader
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}