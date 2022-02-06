#include "InitVisitor.h"

InitVisitor::~InitVisitor()
{

}

void InitVisitor::visit(Group &g)
{
  NodeVisitor::visit(g);
  g.getState()->setProgram(m_program);
}

void InitVisitor::visit(Transform &t)
{
  std::cout << "InitVisitor: Visit transform!" << std::endl;
  t.getState()->setProgram(m_program);
}

void InitVisitor::visit(Geometry &g)
{
  std::cout << "InitVisitor: Visit Geometry" << std::endl;
  if(!g.initShaders(m_program))
  {
      std::cerr << "Failed to load shaders for geometry" << std::endl;
      return;
    }
  g.upload();
  g.getState()->setProgram(m_program);

}