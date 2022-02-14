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
  virtual void visit(Group &g) = 0;
  virtual void visit(Transform &t) = 0;
  virtual void visit(Geometry &g) = 0;
  void traverse(Group &group);
  void traverse(Transform &t);
};