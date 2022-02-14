#pragma once

#include "Geometry.h"
#include "Node.h"
#include <memory>
#include "BoundingBox.h"
#include "UpdateCallback.h"

/**
 * @brief Group class grouping together nodes.
 *        Can be used to logically group nodes
 *        together.
 * 
 */
class Group : public Node {
public:
  /**
   * @brief Construct a new Group object
   * 
   */
  Group();
  ~Group();

  /**
   * @brief Calculate boundingbox for this group;
   * 
   * @param modelMat 
   * @return BoundingBox 
   */
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;

  /**
   * @brief Add a new child to this group
   * 
   * @param node New node to this group.
   */
  void addChild(std::shared_ptr<Node> node);

  /**
   * @brief Check if this group contains any childrne
   * 
   * @return true if empty
   * @return false contains children
   */
  bool empty();

  /**
   * @brief Get the Children
   * 
   * @return NodeVector 
   */
  NodeVector getChildren();

  virtual void accept(NodeVisitor &visitor) override;

protected:
  //Protected such as transform can access this array.
  NodeVector m_nodes;
};

typedef std::vector<std::shared_ptr<Group>> GroupVector;