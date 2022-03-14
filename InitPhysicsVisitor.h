
#pragma once

#include "BoundingBox.h"
#include "NodeVisitor.h"
#include "PhysicsState.h"
#include "Transform.h"
#include "PhysicsCallback.h"
#include <queue>
#include <glm/gtx/io.hpp>

#define BOX 0
#define SPHERE 1

class InitPhysicsVisitor : public NodeVisitor
{
public:
  InitPhysicsVisitor(reactphysics3d::PhysicsCommon *physicsCommon, reactphysics3d::PhysicsWorld* world);
  void initStaticBodies(bool staticBodies);
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;

private:

  std::shared_ptr<PhysicsState> initPhysics(Transform &t, glm::vec3 scale);

  bool m_static;

  reactphysics3d::PhysicsCommon* m_physicsCommon;
  reactphysics3d::PhysicsWorld* m_physicsWorld;
  std::stack<glm::mat4> m_transformStack;
  std::shared_ptr<PhysicsState> m_currentPhysics;
  std::stack<Transform*> m_transformObjStack;
  
};