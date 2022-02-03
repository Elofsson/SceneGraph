#pragma once

#include "NodeVisitor.h"
//TODO Node visitor to handle rendering.
//TODO Apply transformations, states, geometry when encountrered in scenegraph.
//TODO Scenegraph should not be modified by this visitor.
//TODO When transformation matrix is visited, push and concatinate matrix to stack.
//TODO Each drawable object has its own model transform.
//TODO When leaving trasformation node, pop the matrix stack.


class RenderVisitor : public NodeVisitor
{
public:
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
};