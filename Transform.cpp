#include "Transform.h"


Transform::Transform()
{
  object2world = glm::mat4(1.0f);
}

Transform::~Transform()
{

}

BoundingBox Transform::calculateBoundingBox(MeshVector meshVec)
{

}