#pragma once

#include "Group.h"
#include "Debug.h"
#include <stack>

//TODO implement Transform.
/*
 * A Node that transforms all nodes below it in the scenegraph. 
 * Note that you should not change (recalculate vertices positions) the nodes 
 * below the transform when doing this, that would give you trouble when using 
 * instantiation. See notes on RenderVisitor below for possible solutions.
 *
 * 
 * */

//class Group;

class Transform : public Group {

public:
  //TODO consider making this matrix private.
  glm::mat4 object2world;

  Transform();
  ~Transform();
  bool initShaders(GLuint program);
  void pushMat4(glm::mat4 matrix);
  void popMat4(glm::mat4 matrix);
  virtual BoundingBox calculateBoundingBox(MeshVector meshVec) override;
  virtual void accept(NodeVisitor &visitor) override;

private:
  GLuint m_uniform_m;
  GLuint m_uniform_m_3x3_inv_transp;
};