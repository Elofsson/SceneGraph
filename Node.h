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

  std::shared_ptr<State> getState();
  void addCallback(std::shared_ptr<UpdateCallback> callback);
  void executeCallbacks();
  CallbackVector getCallbacks();
  void setState(std::shared_ptr<State> state);
  void setEnabled(bool enabled);
  bool isEnabled();
  bool emptyState();

private:
  std::shared_ptr<State> m_nodeState;
  CallbackVector m_callbacks;
  bool m_enabled;
  

};

typedef std::vector<std::shared_ptr<Node>> NodeVector;
