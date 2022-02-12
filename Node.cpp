#include "Node.h"

Node::Node()
{
}

void Node::accept(NodeVisitor &visitor)
{
}

bool Node::emptyState()
{
  return m_nodeState == NULL;
}

void Node::addCallback(std::shared_ptr<UpdateCallback> callback)
{
  m_callbacks.push_back(callback);
}

void Node::executeCallbacks()
{
  for(int i = 0; i < m_callbacks.size(); i++)
  {
    m_callbacks[i]->update();
  }
}

void Node::setState(std::shared_ptr<State> state) { m_nodeState = state; }

std::shared_ptr<State> Node::getState() { return m_nodeState; }

