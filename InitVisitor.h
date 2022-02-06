#pragma once

#include "NodeVisitor.h"
#include "Transform.h"

class InitVisitor : public NodeVisitor 
{
public:
  using NodeVisitor::NodeVisitor;
  ~InitVisitor();
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
};