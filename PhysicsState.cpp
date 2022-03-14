#include "PhysicsState.h"


PhysicsState::PhysicsState()
{
  //Defaults.
  m_bounciness = 0.2;
  m_friction = 0.1;
  m_mass = 1;
  m_shape = SHAPE_BOX;
  m_type = reactphysics3d::BodyType::STATIC;
}

reactphysics3d::RigidBody* PhysicsState::getBody()
{
  return m_body;
}

void PhysicsState::setCollider(reactphysics3d::Collider* collider)
{
  m_collider = collider;
}

void PhysicsState::setBody(reactphysics3d::RigidBody* body)
{
  //TODO check how the physics library handles memory allocation, and if i am responsible for freeing here.
  m_body = body;
}

void PhysicsState::setBounciness(float bouncy)
{
  m_bounciness = bouncy;
}

void PhysicsState::setMass(float mass)
{
  m_mass = mass;
}

void PhysicsState::setFriction(float friction)
{
  m_friction = friction;
}

void PhysicsState::setShape(int shape)
{
  m_shape = shape;
}

int PhysicsState::getShape()
{
  return m_shape;
}

void PhysicsState::setType(reactphysics3d::BodyType type)
{
  m_type = type;
}

void PhysicsState::init()
{
  m_body->setMass(m_mass);
  m_body->setType(m_type);

  m_collider->getMaterial().setBounciness(m_bounciness);
  m_collider->getMaterial().setFrictionCoefficient(m_friction);
}
