#include "Camera.hpp"

Camera::Camera() :
	m_ZNear(0.1f), m_ZFar(100.0f), 
	m_windowWidth(800), m_windowHeight(600), 
	m_fovy(glm::radians(60.0f)),
	m_yaw(0), m_pitch(0), 
	m_translation(0.0f, 0.0f, 0.0f),
	m_projectionMatrix(1.0f),
	m_viewMatrix(1.0f)
{
	_updateViewMatrix();
	_updateProjectionMatrix();
}

void Camera::setTranslation(glm::vec3 translation)
{
	m_translation = translation;
	_updateViewMatrix();
}
void Camera::translate(glm::vec3 offset)
{
	m_translation += offset;
	_updateViewMatrix();
}
void Camera::setRotation(float yaw, float pitch)
{
	m_yaw = yaw;
	m_pitch = pitch;
	_updateViewMatrix();
}
void Camera::rotate(float deltaYaw, float deltaPitch)
{
	m_yaw += deltaYaw;
	//if (m_yaw > 6.28 || m_yaw < 0) m_yaw = 0;
	m_pitch += deltaPitch;
	if (m_pitch > 1.5) m_pitch = 1.5;
	if (m_pitch < -1.5) m_pitch = -1.5;
	_updateViewMatrix();
}
void Camera::_updateViewMatrix()
{
	glm::vec3 dir(1.0f);
	dir.x = cos(m_yaw) * cos(m_pitch);
	dir.y = sin(m_pitch);
	dir.z = sin(m_yaw) * cos(m_pitch);
	
	/*std::cout << "\nCAMERA INFO\n";
	std::cout << "dir ( " << dir.x << "; " << dir.y << "; " << dir.z << " )\n";
	std::cout << "pos ( " << m_translation.x << "; " << m_translation.y << "; " << m_translation.z << " )\n";
	std::cout << "yaw ( " << m_yaw << " ); pitch (" << m_pitch << " )\n";
	std::cout << "cos yaw ( " << cos(m_yaw) << " ); pitch (" << m_pitch << " )\n";*/

	m_viewMatrix = glm::lookAt(m_translation, m_translation + dir, glm::vec3(0.0f, 1.0f, 0.0f));
}
glm::vec3 Camera::getTranslation()
{
	return m_translation;
}
float Camera::getYaw()
{
	return m_yaw;
}
float Camera::getPitch()
{
	return m_pitch;
}
glm::vec3 Camera::getDirection()
{
	glm::vec3 dir(1.0f);
	dir.x = cos(m_yaw) * cos(m_pitch);
	dir.y = sin(m_pitch);
	dir.z = sin(m_yaw) * cos(m_pitch);
	return dir;
}

void Camera::setWindowSize(int w, int h)
{
	m_windowWidth = w;
	m_windowHeight = h;
	_updateProjectionMatrix();
}
void Camera::_updateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(m_fovy, (float)m_windowWidth / m_windowHeight, m_ZNear, m_ZFar);
}
void Camera::setClippingPlanes(float znear, float zfar)
{
	m_ZNear = znear;
	m_ZFar = zfar;
	_updateProjectionMatrix();
}
void Camera::setFovy(float fovy)
{
	m_fovy = fovy;
	_updateProjectionMatrix();
}
glm::vec2 Camera::getWindowSize()
{
	return glm::vec2(m_windowWidth, m_windowHeight);
}
float Camera::getNearClippingPlane()
{
	return m_ZNear;
}
float Camera::getFarClippingPlane()
{
	return m_ZFar;
}
float Camera::getFovy()
{
	return m_fovy;
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}
glm::mat4 Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}
