#pragma once

#include "NodeVisitor.h"
#include <stack>
//TODO Execute UpdateCallback nodes might have. 
//TODO Derived from the NodeVisitor.
//TODO For each visited node, call UpdateCallback.


class UpdateVisitor : public NodeVisitor
{
public:
  using NodeVisitor::NodeVisitor;
  using NodeVisitor::visit;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
};