#include "ControllableLightCallback.h"


ControllableLightCallback::ControllableLightCallback(std::shared_ptr<Light> light, std::shared_ptr<Camera> camera, std::shared_ptr<Transform> transform)
{
  m_light = light;
  m_camera = camera;
  m_type = m_light->getPosition()[3];
  m_lightGeometry = transform;
  m_lightGeometry->calculateBoundingBox(glm::mat4(1.0f));
}

void ControllableLightCallback::update()
{
  glm::vec4 cameraPos = glm::vec4(m_camera->getPosition(), m_type);
  m_light->setPosition(cameraPos);

  BoundingBox box = m_lightGeometry->getBoundingBox();
  float posOffset = box.getRadius() * 1.25;
  cameraPos.y = cameraPos.y + posOffset;
  m_lightGeometry->setPosition(cameraPos);
}