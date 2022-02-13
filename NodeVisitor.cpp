#include "NodeVisitor.h"
#include "Transform.h"

using namespace std;

NodeVisitor::NodeVisitor(GLuint program)
{
  m_program = program;
  //cout << "NodeVisitor constructor" << endl;
}

NodeVisitor::NodeVisitor()
{
}

NodeVisitor::~NodeVisitor()
{
}

//Group traversal implementation?
void NodeVisitor::visit(Group &g)
{
  //cout << "NodeVisitor: Visit group " << endl;
  g.traverse(*this);
}

void NodeVisitor::visit(Transform &t)
{
  t.traverse(*this);
}
