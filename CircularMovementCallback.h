#pragma once

#include "UpdateCallback.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class CircularMovementCallback : public UpdateCallback
{
public:
  CircularMovementCallback(float speed, float radius);
  virtual bool update(Transform &t) override;
  virtual bool update(Group &t){ return false; };
  virtual bool update(Geometry &t){ return false; };

private:
  float m_speed;
  float m_angle;
  float m_radius;
};