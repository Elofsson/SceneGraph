#include "Group.h"
#include "NodeVisitor.h"
#include "Debug.h"

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
  if(isEnabled())
  {
    visitor.visit(*this);
  }
}

NodeVector Group::getChildren()
{
  return m_nodes;
}

BoundingBox Group::calculateBoundingBox(glm::mat4 modelMat)
{
  BoundingBox box;
  for(auto child : m_nodes)
  {
    BoundingBox boxChild = child->calculateBoundingBox(modelMat);
    box.expand(boxChild);
  }
  m_boundingBox = box;
  return box;
}

