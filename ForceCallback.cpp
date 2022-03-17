#include "ForceCallback.h"

ForceCallback::ForceCallback(std::shared_ptr<PhysicsState> physics, glm::vec3 force)
{
  m_physics = physics;
  m_force = force;
}

void ForceCallback::update()
{
  auto body = m_physics->getBody();
  if(body)
  {
    body->applyLocalForceAtCenterOfMass(reactphysics3d::Vector3(m_force.x, m_force.y, m_force.z));
  }
}