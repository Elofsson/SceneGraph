#pragma once

#include "UpdateCallback.h"
#include "Light.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include "Debug.h"

class MovingTransformCallback : public UpdateCallback
{
public:
  MovingTransformCallback(std::shared_ptr<Transform> transform, glm::vec3 origin, float radius);
  virtual void update() override;
private:
  std::shared_ptr<Transform> m_transform;
  glm::vec3 m_origin;
  float m_radius;
};