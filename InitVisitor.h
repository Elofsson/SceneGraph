#pragma once

#include "NodeVisitor.h"

class InitVisitor : public NodeVisitor 
{
public:
  using NodeVisitor::NodeVisitor;
  ~InitVisitor();
  using NodeVisitor::visit;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
};