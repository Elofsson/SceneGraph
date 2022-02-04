#include "InitVisitor.h"

InitVisitor::~InitVisitor()
{

}

void InitVisitor::visit(Transform &t)
{
  std::cout << "InitVisitor: Visit transform!" << std::endl;
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
}