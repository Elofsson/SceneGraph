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

//----------------------Callbacks---------------------------
void Node::addCallback(std::shared_ptr<UpdateCallback> callback, bool executeOnce)
{
  if(executeOnce)
  {
    m_exec_once_callbacks.push_back(callback);
  }

  else
  {
    m_callbacks.push_back(callback);
  }
}

CallbackVector Node::getCallbacks()
{
  return m_callbacks;
}