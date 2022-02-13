#include "UpdateVisitor.h"

void UpdateVisitor::visit(Group &g)
{
  //std::cout << "Visit group" << std::endl;
  g.executeCallbacks();
  NodeVisitor::visit(g);
}

void UpdateVisitor::visit(Transform &t)
{
  //std::cout << "Visit transform " << std::endl;
  t.executeCallbacks();
  NodeVisitor::visit(t);
}

void UpdateVisitor::visit(Geometry &g)
{
  //std::cout << "Visit geometry " << std::endl;
  g.executeCallbacks();
}
