#include "CircularMovementCallback.h"


CircularMovementCallback::CircularMovementCallback(float speed, float radius, std::shared_ptr<Transform> transform)
{
  //Maximum speed is 90.
  if(speed > 90)
  {
    speed = 90.0f;
  }
  m_transform = transform;
  m_angle = 90.0f;
  m_speed = speed;
  m_radius = radius;
}

void CircularMovementCallback::update()
{
  float xCoord = m_transform->object2world[0][3];
  float yCoord = m_transform->object2world[1][3];
  float zCoord = m_transform->object2world[2][3];

  double newX = xCoord + m_radius * sin(m_angle);
  double newZ = zCoord + m_radius * cos(m_angle);

  //Increase angle.
  m_angle += m_speed;

  //Apply translation.
  glm::vec3 translation = glm::vec3(newX, yCoord, newZ);
  glm::mat4 finalTranslation = glm::translate(glm::mat4(1.0f), translation);
  m_transform->object2world = finalTranslation * m_transform->object2world;
}
