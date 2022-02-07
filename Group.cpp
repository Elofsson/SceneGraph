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
  if(m_nodes.size() > 1)
  {
    std::cout << "Group: " << m_nodes.size() << std::endl;
  }
  for(auto child : m_nodes)
  {
    //std::cout << "Group::accept: Visiting " << child << std::endl;
    child->accept(visitor);
  }
}

BoundingBox Group::calculateBoundingBox(glm::mat4 modelMat)
{
  BoundingBox box;
  for(auto child : m_nodes)
  {
    BoundingBox boxChild = child->calculateBoundingBox(modelMat);
    box.expand(boxChild);
  }
  return box;
}

