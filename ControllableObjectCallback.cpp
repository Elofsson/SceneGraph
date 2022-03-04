#include "ControllableObjectCallback.h"


ControllableObjectCallback::ControllableObjectCallback(std::shared_ptr<Camera> camera, std::shared_ptr<Transform> transform)
{
  m_camera = camera;
  m_transform = transform;
  m_transform->calculateBoundingBox(glm::mat4(1.0f));
}

void ControllableObjectCallback::update()
{
  glm::vec3 cameraPos = m_camera->getPosition();
  BoundingBox box = m_transform->getBoundingBox();
  float posOffset = box.getRadius() * 1.25;
  cameraPos.y = cameraPos.y + posOffset;
  m_transform->setPosition(cameraPos);
}