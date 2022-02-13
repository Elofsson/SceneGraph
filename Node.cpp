#include "Node.h"
#include <iostream>

Node::Node()
{
  m_enabled = true;
}

bool Node::emptyState()
{
  return m_nodeState == nullptr;
}

void Node::addCallback(std::shared_ptr<UpdateCallback> callback)
{
  //std::cout << "Add callback" << std::endl;
  m_callbacks.push_back(callback);
}

CallbackVector Node::getCallbacks()
{
  return m_callbacks;
}

void Node::executeCallbacks()
{
  //std::cout << "Execute callbacks for node " << name  << " Number of callbacks " << m_callbacks.size() << std::endl;
  for(int i = 0; i < m_callbacks.size(); i++)
  {
    m_callbacks[i]->update();
  }
}

void Node::setEnabled(bool enabled)
{
  m_enabled = enabled;
}

bool Node::isEnabled()
{
  return m_enabled;
}

void Node::setState(std::shared_ptr<State> state) { m_nodeState = state; }

std::shared_ptr<State> Node::getState() { return m_nodeState; }

