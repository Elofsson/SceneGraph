#include "PhysicsCallback.h"

PhysicsCallback::PhysicsCallback(Transform *transform, std::shared_ptr<PhysicsState> physics)
{
  m_transform = transform;
  
  m_physicsState = physics; 
  const reactphysics3d::Vector3& position = m_physicsState->getBody()->getTransform().getPosition();
  
  float x = position.x - m_transform->object2world[3][0];
  float y = position.y - m_transform->object2world[3][1];
  float z = position.z - m_transform->object2world[3][2];
  m_physicLocalPos = glm::vec3(x, y, z);
  std::cout << "Start diff " << m_physicLocalPos << std::endl;
}

void PhysicsCallback::update()
{
  reactphysics3d::RigidBody *body = m_physicsState->getBody();

  if(!body->isSleeping())
  {
    const reactphysics3d::Transform& transform = body->getTransform();
    const reactphysics3d::Vector3& position = transform.getPosition();

    //Calculate new position.
    glm::vec3 pos(position.x, position.y, position.z);
    glm::vec3 newPos = pos - m_physicLocalPos;
    //std::cout << "Position: " << pos << std::endl;

    m_transform->setPosition(newPos);    
  }
}