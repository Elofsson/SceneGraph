#include "PhysicsState.h"


PhysicsState::PhysicsState()
{
  //Defaults.
  m_bounciness = 0.2;
  m_friction = 0.1;
  m_mass = 1;
  m_shape = SHAPE_BOX;
  m_type = reactphysics3d::BodyType::STATIC;
  m_body = nullptr;
  m_force = reactphysics3d::Vector3(0, 0, 0);
}

PhysicsState::PhysicsState(PhysicsState &inState)
{
  m_bounciness = inState.getBounciness();
  m_friction = inState.getFriction();
  m_mass = inState.getMass();
  m_shape = inState.getShape();
  m_type = inState.getType();
  m_force = inState.getForce();
}

void PhysicsState::setForce(reactphysics3d::Vector3 force)
{
  m_force = force;
}

reactphysics3d::RigidBody* PhysicsState::getBody()
{
  return m_body;
}

void PhysicsState::addCollider(reactphysics3d::Collider* collider)
{
  m_colliders.push_back(collider);
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

void PhysicsState::setType(reactphysics3d::BodyType type)
{
  m_type = type;
}

reactphysics3d::Vector3 PhysicsState::getForce()
{
  return m_force;
}

float PhysicsState::getBounciness()
{
  return m_bounciness;
}

float PhysicsState::getMass()
{
  return m_mass;
}

float PhysicsState::getFriction()
{
  return m_friction;
}

int PhysicsState::getShape()
{
  return m_shape;
}

reactphysics3d::BodyType PhysicsState::getType()
{
  return m_type;
}

bool PhysicsState::haveColliders()
{
  return !m_colliders.empty();
}

void PhysicsState::init()
{
  m_body->setMass(m_mass);
  m_body->setType(m_type);

  for(auto collider : m_colliders)
  {
    collider->getMaterial().setBounciness(m_bounciness);
    collider->getMaterial().setFrictionCoefficient(m_friction);
  }

  //Apply force.
  m_body->applyLocalForceAtCenterOfMass(m_force);
}
