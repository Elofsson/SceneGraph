#include "UpdateVisitor.h"

void UpdateVisitor::visit(Transform &t)
{
  std::cout << "UpdateVisitor::Visit Transform" << std::endl;
}
void UpdateVisitor::visit(Geometry &g)
{
  std::cout << "UpdateVisitor::Visit Geometry" << std::endl;
}
