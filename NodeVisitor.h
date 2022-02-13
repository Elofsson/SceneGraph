#pragma once

#include <GL/glew.h>

#include "Group.h"
#include "glm/glm.hpp"
#include <iostream>
#include <stack>

class Transform;
class Group;
class Geometry;

class NodeVisitor 
{
public:
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