
#pragma once

#include "NodeVisitor.h"
#include "Transform.h"

class PhysicsVisitor : public NodeVisitor
{
public:
  PhysicsVisitor();
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;

private:

  void updatePhysics(Node &g);

  std::stack<glm::mat4> m_transform_matrices;
  std::shared_ptr<PhysicsState> m_currentPhysics;
};