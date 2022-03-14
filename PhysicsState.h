#pragma once

#include <reactphysics3d/reactphysics3d.h>

#define SHAPE_BOX 0
#define SHAPE_SPHERE 1

class PhysicsState
{

public:
  PhysicsState();
  reactphysics3d::RigidBody* getBody();
  void setCollider(reactphysics3d::Collider* collider);
  void setBounciness(float bouncy);
  void setMass(float mass);
  void setFriction(float friction);
  void setShape(int shape);
  void setType(reactphysics3d::BodyType type);
  void setBody(reactphysics3d::RigidBody* body);

  int getShape();

  void init();

private:
  reactphysics3d::RigidBody* m_body;
  reactphysics3d::Collider* m_collider;
  reactphysics3d::BodyType m_type;
  float m_bounciness;
  float m_mass;
  float m_friction;
  int m_shape;
};