#pragma once

#include "Geometry.h"
#include "Node.h"
#include <memory>
#include "BoundingBox.h"
//TODO implement group.

class Group : public Node {
public:
  Group();
  ~Group();
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;

  //TODO check if shared pointers should be used or not.
  void addChild(std::shared_ptr<Node> node);

  //Check if this group contains any children.
  bool empty();

  virtual void accept(NodeVisitor &visitor) override;

protected:
  NodeVector m_nodes;
};

typedef std::vector<std::shared_ptr<Group>> GroupVector;