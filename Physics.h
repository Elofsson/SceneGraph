#pragma once

#include "Node.h"
#include "InitPhysicsVisitor.h"
#include "Camera.h"
#include "PhysicsVisitor.h"
#include <vr/shaderUtils.h>

class Physics
{
public:
  Physics();
  bool init(const std::string& vshader_filename, const std::string& fshader_filename);
  void add(std::shared_ptr<Group> node, int shape, bool staticBody);
  void update(Group &group);
  void renderCollisionBoxes(std::shared_ptr<Camera> camera);

private:
  void enableDebug();

  GLuint m_program;
  GLuint m_verticesLocation;

  float m_timeStep;  
  std::shared_ptr<InitPhysicsVisitor> m_physicsVisitor;
  std::shared_ptr<PhysicsVisitor> m_physicsUpdater;
  reactphysics3d::PhysicsCommon* m_physicsCommon;
  reactphysics3d::PhysicsWorld* m_physicsWorld;
};