#pragma once

#include "Geometry.h"
#include "Node.h"
//TODO implement group.

class Group : public Node {
public:
  Group();
  virtual BoundingBox calculateBoundingBox(MeshVector meshVec) override;

  //TODO check if shared pointers should be used or not.
  void addChild(std::shared_ptr<Node> node);
  void addChild(std::shared_ptr<Group> group);
  void addChild(std::shared_ptr<Geometry> geometry);

  //Check if this group contains any children.
  bool empty();

  //TODO Temporary method to test functionality. Look further into how the scene can init geometry with shaders.
  GeometryVector getGeometry();
};

typedef std::vector<std::shared_ptr<Group>> GroupVector;