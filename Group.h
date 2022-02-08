#pragma once

#include "Geometry.h"
#include "Node.h"
#include <memory>
#include "BoundingBox.h"
#include "UpdateCallback.h"
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
  virtual void addCallback(std::shared_ptr<UpdateCallback<Group>> callback);
  virtual void executeCallbacks();

protected:
  NodeVector m_nodes;

private:
  std::vector<std::shared_ptr<UpdateCallback<Group>>> m_callbacks;
};

typedef std::vector<std::shared_ptr<Group>> GroupVector;