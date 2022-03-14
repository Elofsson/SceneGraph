#include "UpdateVisitor.h"

void UpdateVisitor::visit(Group &g)
{
  g.executeCallbacks();

  NodeVisitor::traverse(g);
}

void UpdateVisitor::visit(Transform &t)
{
  //std::cout << "Visiting transform in updatevisitor: " << &t << std::endl;
  t.executeCallbacks();

  NodeVisitor::traverse(t);
}

void UpdateVisitor::visit(Geometry &g)
{
  g.executeCallbacks();
}
