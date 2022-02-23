#include "ControllableLightCallback.h"


ControllableLightCallback::ControllableLightCallback(std::shared_ptr<Light> light, std::shared_ptr<Camera> camera)
{
  m_light = light;
  m_camera = camera;
}

void ControllableLightCallback::update()
{
  glm::vec4 cameraPos = glm::vec4(m_camera->getPosition(), 1.0);
  m_light->setPosition(cameraPos);
}