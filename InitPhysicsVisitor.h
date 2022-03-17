
#pragma once

#include "BoundingBox.h"
#include "NodeVisitor.h"
#include "PhysicsState.h"
#include "Transform.h"
#include "PhysicsCallback.h"
#include <glm/gtx/io.hpp>

//TODO enum?
#define BOX 0
#define SPHERE 1

class InitPhysicsVisitor : public NodeVisitor
{
public:
  InitPhysicsVisitor(reactphysics3d::PhysicsCommon *physicsCommon, reactphysics3d::PhysicsWorld* world);
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;

private:

  std::shared_ptr<PhysicsState> initPhysics(Transform &t, BoundingBox box, Geometry &g);

  //Physics attributes used for initalizing and storing physics.
  reactphysics3d::PhysicsCommon* m_physicsCommon;
  reactphysics3d::PhysicsWorld* m_physicsWorld;

  //Stack of matrices used to set position of rigied bodies and collision boxes.
  std::stack<glm::mat4> m_transformStack;

  //Stack of transform objects used to init the physic states for correct transforms.
  std::stack<Transform*> m_transformObjStack;
  
};