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
  for(auto child : m_nodes)
  {
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

void Group::addCallback(std::shared_ptr<UpdateCallback<Group>> callback)
{
  m_callbacks.push_back(callback);
}

void Group::executeCallbacks()
{
  for(int i = 0; i < m_callbacks.size(); i++)
  {
    m_callbacks[i]->update(*this);

    if(m_callbacks[i]->callOnce())
    {
      m_callbacks.erase(m_callbacks.begin() + i);
    }
  }
}

