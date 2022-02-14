#include "MovingLightCallback.h"

MovingLightCallback::MovingLightCallback(std::shared_ptr<Transform> transform, std::shared_ptr<Light> lightSource)
{
  m_transform = transform;
  m_light = lightSource;
}

void MovingLightCallback::update()
{

  glm::vec4 lightPos = m_light->getPosition();

  float x = 1.0f + sin(glfwGetTime()) * lightPos.y;
  float z = 1.0f + cos(glfwGetTime()) * lightPos.y;
  
    //Apply translation to light.
  m_light->setPosition(glm::vec4(x, lightPos.y, z, lightPos.w));

  m_transform->object2world = glm::mat4(1.0f);
  m_transform->object2world = glm::translate(m_transform->object2world, glm::vec3(m_light->getPosition()));

}