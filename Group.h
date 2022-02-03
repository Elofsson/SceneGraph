#pragma once

#include "Geometry.h"
#include "Node.h"
//TODO implement group.

class Group : public Node {
public:
  Group();
  ~Group();
  virtual BoundingBox calculateBoundingBox(MeshVector meshVec) override;

  //TODO check if shared pointers should be used or not.
  void addChild(std::shared_ptr<Node> node);

  //Check if this group contains any children.
  bool empty();
};

typedef std::vector<std::shared_ptr<Group>> GroupVector;