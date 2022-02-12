#include "UpdateVisitor.h"

void UpdateVisitor::visit(Group &g)
{
  g.executeCallbacks();
  NodeVisitor::visit(g);
}

void UpdateVisitor::visit(Transform &t)
{
  t.executeCallbacks();
  NodeVisitor::visit(t);
}

void UpdateVisitor::visit(Geometry &g)
{
  g.executeCallbacks();
}
