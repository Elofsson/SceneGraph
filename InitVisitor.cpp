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
  NodeVisitor::traverse(g);
}

void InitVisitor::visit(Transform &t)
{
  NodeVisitor::traverse(t);
}

void InitVisitor::visit(Geometry &g)
{
  std::cout << "Init geometry with program: " << m_program << std::endl;
  if(!g.initShaders(m_program))
  {
      std::cerr << "Failed to load shaders for geometry" << std::endl;
      return;
    }
  g.upload();
  //g.getState()->setProgram(m_program);

}