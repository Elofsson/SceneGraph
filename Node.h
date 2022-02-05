#pragma once

#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "BoundingBox.h"

#include <glm/glm.hpp>

class NodeVisitor;

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
  
  //TODO Add other visitors here later.
  //TODO Should nodes be able to add geometry, or only groups?
  virtual void accept(NodeVisitor& visitor) = 0;

private:

};

typedef std::vector<std::shared_ptr<Node>> NodeVector;
