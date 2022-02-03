#pragma once

#include "Group.h"
#include "Geometry.h"
#include "Transform.h"
#include <iostream>

//TODO Abstract baseclass for nodevisitors used to traverse scene graph.
//TODO Implement group traversing. 
//TODO Check out the visitor pattern.


class NodeVisitor 
{
public:
  NodeVisitor(GLuint program);
  virtual ~NodeVisitor();
  virtual void visit(Group &g);
  virtual void visit(Transform &t) = 0;
  virtual void visit(Geometry &g) = 0;

protected:
  GLuint m_program;
};