#pragma once

#include <GL/glew.h>

#include "Group.h"
#include "glm/glm.hpp"
#include <iostream>
#include <stack>

//TODO Abstract baseclass for nodevisitors used to traverse scene graph.
//TODO Implement group traversing. 
//TODO Check out the visitor pattern.

class Transform;
class Group;
class Geometry;

class NodeVisitor 
{
public:
  NodeVisitor(GLuint program);
  NodeVisitor();
  virtual ~NodeVisitor();
  virtual void visit(Group &g);
  virtual void visit(Transform &t);
  virtual void visit(Geometry &g) = 0;

protected:
  GLuint m_program;

private:
  void traverse(Group &group);
};