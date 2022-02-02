#pragma once

#include "Node.h"

//TODO Abstract baseclass for nodevisitors used to traverse scene graph.
//TODO Implement group traversing. 
//TODO Check out the visitor pattern.


class NodeVisitor 
{
public:
  void visitNode(Node *node);
};