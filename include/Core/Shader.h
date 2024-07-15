#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Core {

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    bool isValid() const { return m_Program != 0; }
    void use();
    
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    GLuint m_Program;
    std::unordered_map<std::string, GLint> m_UniformLocationCache;

    void checkCompileErrors(GLuint shader, std::string type);
    GLint getUniformLocation(const std::string& name);
};

} // namespace Core