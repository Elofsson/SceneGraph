#include "Node.h"

Node::Node()
{
  nodeState = std::shared_ptr<State>(new State());
}

void Node::accept(NodeVisitor &visitor)
{
  //visitor.visit(this);
  
}

std::shared_ptr<State> Node::getState() { return nodeState; }

