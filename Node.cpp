#include "Node.h"

Node::Node()
{
}

void Node::accept(NodeVisitor &visitor)
{
  //visitor.visit(this);
}

/// Calculate and return a bounding box for this Node based on its Mesh objects
//BoundingBox Node::calculateBoundingBox(MeshVector meshVec)
//{
  //BoundingBox box;

  /*for (auto m : m_meshes)
  {
    BoundingBox meshBox = m->calculateBoundingBox();
    meshBox = meshBox * this->object2world;
    box.expand(meshBox);
  }*/

  //return box;
//}