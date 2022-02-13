#include "InitVisitor.h"

InitVisitor::InitVisitor(GLuint program)
{
  m_program = program;
}

InitVisitor::~InitVisitor()
{
}

void InitVisitor::visit(Group &g)
{
  NodeVisitor::visit(g);
}

void InitVisitor::visit(Transform &t)
{
  NodeVisitor::visit(t);
}

void InitVisitor::visit(Geometry &g)
{
  if(!g.initShaders(m_program))
  {
      std::cerr << "Failed to load shaders for geometry" << std::endl;
      return;
    }
  g.upload();
  g.getState()->setProgram(m_program);

}