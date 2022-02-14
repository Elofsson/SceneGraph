#pragma once

#include "UpdateCallback.h"
#include "Light.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include "Debug.h"

class MovingLightCallback : public UpdateCallback
{
public:
  MovingLightCallback(std::shared_ptr<Transform> transform, std::shared_ptr<Light> lightSource);
  virtual void update() override;
private:
  std::shared_ptr<Transform> m_transform;
  std::shared_ptr<Light> m_light;
};