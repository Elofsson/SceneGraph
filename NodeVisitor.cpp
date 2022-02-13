#include "NodeVisitor.h"
#include "Transform.h"

using namespace std;

NodeVisitor::NodeVisitor()
{
}

NodeVisitor::~NodeVisitor()
{
}

void NodeVisitor::visit(Group &g)
{
  g.traverse(*this);
}

void NodeVisitor::visit(Transform &t)
{
  t.traverse(*this);
}
