#include "MovingTransformCallback.h"

MovingTransformCallback::MovingTransformCallback(std::shared_ptr<Transform> transform, glm::vec3 origin, float radius)
{
  m_transform = transform;
  m_origin = origin;
  m_radius = radius;
}

void MovingTransformCallback::update()
{
  //std::cout << "Moving transform callback" << std::endl;
  float x = 3.0f + sin(glfwGetTime()) * m_radius;
  float z = 3.0f + cos(glfwGetTime()) * m_radius;
  
  glm::vec3 newPos = glm::vec3(x, m_origin.y, z);
  m_transform->setPosition(newPos);

  //m_transform->object2world = glm::mat4(1.0f);
  //m_transform->translate(glm::vec3(x, 1, z));

}