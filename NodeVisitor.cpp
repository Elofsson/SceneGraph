#include "NodeVisitor.h"

using namespace std;

NodeVisitor::NodeVisitor(GLuint program)
{
  m_program = program;
  cout << "NodeVisitor constructor" << endl;
}

NodeVisitor::~NodeVisitor()
{

}

//Group traversal implementation?
void NodeVisitor::visit(Group &g)
{
  cout << "NodeVisitor: Visit group" << endl;
  g.accept(*this);
}