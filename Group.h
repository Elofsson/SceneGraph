#pragma once

#include "Geometry.h"
#include "Node.h"
#include <memory>
#include "BoundingBox.h"
#include "UpdateCallback.h"

class Group : public Node {
public:
  Group();
  ~Group();
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;

  void addChild(std::shared_ptr<Node> node);

  //Check if this group contains any children.
  bool empty();
  void traverse(NodeVisitor &visitor);
  NodeVector getChildren();
  virtual void accept(NodeVisitor &visitor) override;

protected:
  NodeVector m_nodes;
};

typedef std::vector<std::shared_ptr<Group>> GroupVector;