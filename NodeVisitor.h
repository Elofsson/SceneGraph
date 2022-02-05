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
  virtual ~NodeVisitor();
  virtual void popMat4();
  virtual void pushMat4(glm::mat4 matrix);
  virtual bool isTransformsEmpty();
  virtual glm::mat4 getLastTransform();
  virtual void visit(Group &g);
  virtual void visit(Transform &t) = 0;
  virtual void visit(Geometry &g) = 0;

protected:
  GLuint m_program;
  std::stack<glm::mat4> m_transform_matrices;
};