#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera
{
public:
	Camera();

	void setTranslation(glm::vec3 translation);
	void translate(glm::vec3 offset);
	void setRotation(float yaw, float pitch);
	glm::vec3 getDirection();
	void rotate(float deltaYaw, float deltaPitch);
	glm::vec3 getTranslation();
	float getYaw();
	float getPitch();
	glm::mat4 getViewMatrix();

		
	void setWindowSize(int w, int h);
	void setClippingPlanes(float znear, float zfar);
	void setFovy(float fovy);
	glm::vec2 getWindowSize();
	float getNearClippingPlane();
	float getFarClippingPlane();
	float getFovy();
	glm::mat4 getProjectionMatrix();
private:
	void _updateViewMatrix();
	void _updateProjectionMatrix();
	glm::mat4 m_projectionMatrix, m_viewMatrix;
	glm::vec3 m_translation;
	float m_yaw, m_pitch;
	float m_ZNear, m_ZFar, m_windowWidth, m_windowHeight, m_fovy;
};