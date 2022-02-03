#include "RenderVisitor.h"

using namespace std;

void RenderVisitor::visit(Transform &t)
{
  cout << "RenderVisitor: visit transform" << endl;
  t.accept(*this);
}

void RenderVisitor::visit(Geometry &g)
{
  cout << "RenderVisitor: visit geometry" << endl;
  g.draw();
}