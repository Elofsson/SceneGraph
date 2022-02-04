#include "Transform.h"
#include "NodeVisitor.h"

Transform::Transform()
{
  object2world = glm::mat4(1.0f);
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
    return 0;
  }

  //FIXME check where this inverse transpose matrix should be set.
  uniform_name = "m_3x3_inv_transp";
  m_uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
  if (m_uniform_m_3x3_inv_transp == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return false;
  }
}

void Transform::accept(NodeVisitor &visitor)
{
  
  //Push transform.
  //Empty stack, add transformation matrix directly.
  if(visitor.isTransformsEmpty())
  {
    visitor.pushMat4(object2world);
  }

  //calculate and concat matrix.
  else
  {
    glm::mat4 prevMat = visitor.getLastTransform();
    glm::mat4 newObject2world = object2world * prevMat;
    visitor.pushMat4(newObject2world); 
  }

  Group::accept(visitor);
  
  //Pop transform.
  visitor.popMat4();
}

BoundingBox Transform::calculateBoundingBox(MeshVector meshVec)
{

}