#pragma once

#include "UpdateCallback.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
#include <iostream>

class ControllableObjectCallback : public UpdateCallback
{

public:
  ControllableObjectCallback(std::shared_ptr<Camera> camera, std::shared_ptr<Transform> transform);
  virtual void update() override;

private:
  std::shared_ptr<Camera> m_camera;
  std::shared_ptr<Transform> m_transform;
};