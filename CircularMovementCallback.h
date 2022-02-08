#pragma once

#include "UpdateCallback.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class CircularMovementCallback : public UpdateCallback<Transform>
{
public:
  CircularMovementCallback(float speed, float radius, bool callOnce);
  virtual bool update(Transform &t) override;

private:
  float m_speed;
  float m_angle;
  float m_radius;
};