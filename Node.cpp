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

void Node::setState(std::shared_ptr<State> state) { m_nodeState = state; }

std::shared_ptr<State> Node::getState() { return m_nodeState; }

