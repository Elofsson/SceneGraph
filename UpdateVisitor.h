#pragma once

#include "NodeVisitor.h"
#include "Geometry.h"
#include "Transform.h"
#include <stack>
//TODO Execute UpdateCallback nodes might have. 
//TODO Derived from the NodeVisitor.
//TODO For each visited node, call UpdateCallback.


class UpdateVisitor : public NodeVisitor
{
public:
  using NodeVisitor::NodeVisitor;
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
};