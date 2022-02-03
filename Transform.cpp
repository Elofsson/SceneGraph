#include "Transform.h"
#include "NodeVisitor.h"

Transform::Transform()
{
  object2world = glm::mat4(1.0f);
}

Transform::~Transform()
{

}

void Transform::accept(NodeVisitor &visitor)
{
  //Push transform.
  Group::accept(visitor);
  //Pop transform.
}

BoundingBox Transform::calculateBoundingBox(MeshVector meshVec)
{

}