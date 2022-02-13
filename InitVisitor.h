#pragma once

#include "NodeVisitor.h"
#include "Transform.h"

class InitVisitor : public NodeVisitor 
{
public:
  InitVisitor(GLuint program);
  ~InitVisitor();
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
private:
  GLuint m_program;
};