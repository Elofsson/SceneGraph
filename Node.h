#pragma once

#include <memory>
#include <string>
#include <vector>
#include "BoundingBox.h"
#include "State.h"
#include <glm/glm.hpp>
#include "UpdateCallback.h"

class NodeVisitor;

//TODO find a way to check if a node has a set state.
/// <summary>
/// Simple class that store a number of meshes and draws it
/// </summary>
class Node
{

public:
  //TODO check if this should be private.
  std::string name;

  Node();

  // Calculate and return a bounding box for this Node based on its Mesh objects
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) = 0;
  
  virtual void accept(NodeVisitor& visitor) = 0;

  //TODO See how state should be able to be modified later, set methods? public attribute? 
  virtual std::shared_ptr<State> getState();
  virtual void setState(std::shared_ptr<State> state);
  virtual bool emptyState();


protected:
  std::shared_ptr<State> m_nodeState;

};

typedef std::vector<std::shared_ptr<Node>> NodeVector;
