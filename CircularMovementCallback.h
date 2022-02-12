#pragma once

#include "UpdateCallback.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class CircularMovementCallback : public UpdateCallback
{
public:
  CircularMovementCallback(float speed, float radius, std::shared_ptr<Transform> transform);
  virtual void update() override;

private:
  float m_speed;
  float m_angle;
  float m_radius;
  std::shared_ptr<Transform> m_transform;
};