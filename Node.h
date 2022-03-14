#pragma once

#include <memory>
#include <string>
#include <vector>
#include "BoundingBox.h"
#include "State.h"
#include <glm/glm.hpp>
#include "UpdateCallback.h"
#include "PhysicsState.h"

class NodeVisitor;

class Node
{

public:
  std::string name;

  Node();

  // Calculate and return a bounding box for this Node based on its Mesh objects
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) = 0;
  virtual BoundingBox getBoundingBox();

  virtual void accept(NodeVisitor& visitor) = 0;

  std::shared_ptr<State> getState();
  virtual void addCallback(std::shared_ptr<UpdateCallback> callback);
  virtual void executeCallbacks();
  CallbackVector getCallbacks();
  
  void setState(std::shared_ptr<State> state);
  void setPhysics(std::shared_ptr<PhysicsState> physicsState);
  std::shared_ptr<PhysicsState> getPhysics();

  void setEnabled(bool enabled);
  bool isEnabled();
  bool emptyState();

private:
  std::shared_ptr<State> m_nodeState;
  std::shared_ptr<PhysicsState> m_physics;
  CallbackVector m_callbacks;
  bool m_enabled;

protected:
  BoundingBox m_boundingBox;

};

typedef std::vector<std::shared_ptr<Node>> NodeVector;
