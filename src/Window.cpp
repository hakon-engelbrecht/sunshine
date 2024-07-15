#include "Core/Window.h"
#include <iostream>

namespace Core {

Window::Window(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr) {}

Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}

bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Window::update() {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::close() {
    glfwSetWindowShouldClose(m_Window, true);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}  // namespace Core