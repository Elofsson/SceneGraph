#include "CircularMovementCallback.h"

CircularMovementCallback::CircularMovementCallback(float speed, float radius, bool callOnce) : UpdateCallback(callOnce)
{
  //Maximum speed is 90.
  if(speed > 90)
  {
    speed = 90.0f;
  }

  m_angle = 90.0f;
  m_speed = speed;
  m_radius = radius;
}

bool CircularMovementCallback::update(Transform &t)
{
  float xCoord = t.object2world[0][3];
  float yCoord = t.object2world[1][3];
  float zCoord = t.object2world[2][3];

  double newX = xCoord + m_radius * sin(m_angle);
  double newZ = zCoord + m_radius * cos(m_angle);

  //Increase angle.
  m_angle += m_speed;

  //Apply translation.
  glm::vec3 translation = glm::vec3(newX, yCoord, newZ);
  glm::mat4 finalTranslation = glm::translate(glm::mat4(1.0f), translation);
  t.object2world = finalTranslation * t.object2world;
  
  return true;
}
