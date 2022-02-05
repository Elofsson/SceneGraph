#include "NodeVisitor.h"

using namespace std;

NodeVisitor::NodeVisitor(GLuint program)
{
  m_program = program;
  //cout << "NodeVisitor constructor" << endl;
}

NodeVisitor::~NodeVisitor()
{

}

//Group traversal implementation?
void NodeVisitor::visit(Group &g)
{
  //cout << "NodeVisitor: Visit group " << endl;
  g.accept(*this);
}

bool NodeVisitor::isTransformsEmpty()
{
  return m_transform_matrices.empty();
}

glm::mat4 NodeVisitor::getLastTransform()
{
  return m_transform_matrices.top();
}

void NodeVisitor::pushMat4(glm::mat4 matrix)
{
  m_transform_matrices.push(matrix);
}

void NodeVisitor::popMat4()
{
  m_transform_matrices.pop();
}
