#pragma once

#include "Group.h"
#include "Debug.h"
#include "UpdateCallback.h"
#include <stack>
#include <glm/gtc/matrix_transform.hpp>

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

class NodeVisitor;

class Transform : public Group {

public:
  //TODO consider making this matrix private.
  glm::mat4 object2world;

  Transform();
  Transform(float x, float y, float z);
  ~Transform();
  void scale(glm::vec3 scale);
  void translate(glm::vec3 translation);
  void rotate(glm::vec3 axis, float angle);
  void setPosition(glm::vec3 position);
  bool initShaders(GLuint program);
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;
  virtual void accept(NodeVisitor &visitor) override;

private:
  void updateObject2world();
  glm::mat4 m_scale;
  glm::mat4 m_rotation;
  glm::mat4 m_translation;

  GLuint m_uniform_m;
  GLuint m_uniform_m_3x3_inv_transp;
};