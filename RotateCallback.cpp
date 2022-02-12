#include "RotateCallback.h"

RotateCallback::RotateCallback(std::shared_ptr<Transform> transform)
{
  m_transform = transform;
}

void RotateCallback::update()
{
  m_transform->object2world = glm::rotate(m_transform->object2world, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
}