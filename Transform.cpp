#include "Transform.h"
#include "NodeVisitor.h"

Transform::Transform()
{
  object2world = glm::mat4(1.0f);
}

Transform::Transform(float x, float y, float z)
{
  object2world = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

Transform::~Transform()
{

}

bool Transform::initShaders(GLuint program)
{
  const char* uniform_name = "m";
  m_uniform_m = glGetUniformLocation(program, uniform_name);
  if (m_uniform_m == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return false;
  }

  //FIXME check where this inverse transpose matrix should be set.
  uniform_name = "m_3x3_inv_transp";
  m_uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
  if (m_uniform_m_3x3_inv_transp == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return false;
  }

  return true;
}

void Transform::accept(NodeVisitor &visitor)
{
  visitor.visit(*this);
}

BoundingBox Transform::calculateBoundingBox(glm::mat4 modelMat)
{
  BoundingBox box;
  glm::mat4 newModelMat = modelMat * object2world;
  for(auto child : m_nodes)
  {
    BoundingBox boxChild = child->calculateBoundingBox(newModelMat);
    box.expand(boxChild);
  }

  return box;
}