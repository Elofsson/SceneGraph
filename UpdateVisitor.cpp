#include "UpdateVisitor.h"

void UpdateVisitor::visit(Transform &t)
{
  std::cout << "UpdateVisitor::Visit Transform" << std::endl;
  CallbackVector callbacks = t.getCallbacks();

  for(auto callback : callbacks)
  {
    callback->update(t);
  }
}
void UpdateVisitor::visit(Geometry &g)
{
  std::cout << "UpdateVisitor::Visit Geometry" << std::endl;
}

void UpdateVisitor::visit(Group &g)
{
  std::cout << "UpdateVisitor::VisitGroup" << std::endl;
  NodeVisitor::visit(g);
}
