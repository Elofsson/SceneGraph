#pragma once

#include "UpdateCallback.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
#include <iostream>

class ControllableLightCallback : public UpdateCallback
{

public:
  ControllableLightCallback(std::shared_ptr<Light> light, std::shared_ptr<Camera> camera, std::shared_ptr<Transform> transform);
  virtual void update() override;

private:
  std::shared_ptr<Camera> m_camera;
  std::shared_ptr<Light> m_light;
  std::shared_ptr<Transform> m_lightGeometry;
  int m_type;
};