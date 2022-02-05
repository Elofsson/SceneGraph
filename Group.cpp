#include "Group.h"
#include "NodeVisitor.h"

Group::Group() 
{ 
}

Group::~Group()
{
}

void Group::addChild(std::shared_ptr<Node> node)
{
  m_nodes.push_back(node);
}

bool Group::empty()
{
  return m_nodes.empty();
}

void Group::accept(NodeVisitor &visitor)
{
  std::cout << "Group: " << (this) << std::endl;
  for(auto child : m_nodes)
  {
    std::cout << "Group::accept: Visiting " << child << std::endl;
    child->accept(visitor);
  }
}

BoundingBox Group::calculateBoundingBox(MeshVector meshVec)
{
  //FIXME fix boundingbox calculation here.
  BoundingBox box;
  return box;
}
