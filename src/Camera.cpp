#include "Core/Camera.h"
#include <glm/gtc/constants.hpp>

namespace Core {

Camera::Camera(float fov, float aspect, float near, float far)
    : m_position(0.0f, 0.0f, 3.0f), m_target(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
      m_fov(fov), m_aspect(aspect), m_near(near), m_far(far),
      m_projectionType(ProjectionType::Perspective), m_orthographicSize(5.0f)
{
    updateVectors();
}

void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
    updateVectors();
}

void Camera::setTarget(const glm::vec3& target) {
    m_target = target;
    updateVectors();
}

void Camera::setUp(const glm::vec3& up) {
    m_up = up;
    updateVectors();
}

void Camera::setFOV(float fov) {
    m_fov = fov;
}

void Camera::setAspectRatio(float aspect) {
    m_aspect = aspect;
}

void Camera::setNearPlane(float near) {
    m_near = near;
}

void Camera::setFarPlane(float far) {
    m_far = far;
}

void Camera::setProjectionType(ProjectionType type) {
    m_projectionType = type;
}

void Camera::setOrthographicSize(float size) {
    m_orthographicSize = size;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    if (m_projectionType == ProjectionType::Perspective) {
        return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    } else {
        float halfSize = m_orthographicSize * 0.5f;
        return glm::ortho(-halfSize * m_aspect, halfSize * m_aspect, -halfSize, halfSize, m_near, m_far);
    }
}

void Camera::pan(float dx, float dy) {
    glm::vec3 offset = m_right * dx + m_up * dy;
    m_position += offset;
    m_target += offset;
}

void Camera::rotate(float dx, float dy) {
    float sensitivity = 0.1f;
    dx *= sensitivity;
    dy *= sensitivity;

    glm::quat quatX = glm::angleAxis(glm::radians(-dy), m_right);
    glm::quat quatY = glm::angleAxis(glm::radians(-dx), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat rotation = quatX * quatY;

    m_front = glm::rotate(rotation, m_front);
    m_up = glm::rotate(rotation, m_up);

    m_target = m_position + m_front;
    updateVectors();
}

void Camera::zoom(float amount) {
    m_position += m_front * amount;
}

void Camera::updateVectors() {
    m_front = glm::normalize(m_target - m_position);
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

} // namespace Core