#pragma once

#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "BoundingBox.h"

#include <glm/glm.hpp>

class Visitor;

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
  virtual BoundingBox calculateBoundingBox(MeshVector meshVec) = 0;
  
  //TODO Add other visitors here later.
  //TODO Should nodes be able to add geometry, or only groups?
  void Accept(Visitor *visitor);

private:

};

typedef std::vector<std::shared_ptr<Node>> NodeVector;
