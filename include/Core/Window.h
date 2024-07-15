#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Core {

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool init();
    void update();
    bool shouldClose() const;
    void close();

    int getWidth() const { return m_Width; }
    int getHeight() const { return m_Height; }
    GLFWwindow* getGLFWwindow() const { return m_Window; }

private:
    int m_Width;
    int m_Height;
    std::string m_Title;
    GLFWwindow* m_Window;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

}  // namespace Core