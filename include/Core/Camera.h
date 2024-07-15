#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Core {

class Camera {
public:
    enum class ProjectionType {
        Perspective,
        Orthographic
    };

    Camera(float fov, float aspect, float near, float far);
    
    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setUp(const glm::vec3& up);

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getTarget() const { return m_target; }
    glm::vec3 getUp() const { return m_up; }

    void setFOV(float fov);
    void setAspectRatio(float aspect);
    void setNearPlane(float near);
    void setFarPlane(float far);

    void setProjectionType(ProjectionType type);
    void setOrthographicSize(float size);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void pan(float dx, float dy);
    void rotate(float dx, float dy);
    void zoom(float amount);

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_up;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;

    ProjectionType m_projectionType;
    float m_orthographicSize;

    void updateVectors();

    glm::vec3 m_front;
    glm::vec3 m_right;
};

} // namespace Core