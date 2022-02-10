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
  //std::cout << "Transform::accept " << this << std::endl;
  //Debug::printMat4(object2world);

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
    glm::mat4 newObject2world = prevMat * object2world;
    visitor.pushMat4(newObject2world); 
  }

  //Go to visitor before searching for other
  visitor.visit(*this);

  Group::accept(visitor);
  
  //Pop transform.
  visitor.popMat4();



  //visit.
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

void Transform::addCallback(std::shared_ptr<UpdateCallback<Transform>> callback)
{
  m_callbacks.push_back(callback);
}

void Transform::executeCallbacks()
{
  for(int i = 0; i < m_callbacks.size(); i++)
  {
    m_callbacks[i]->update(*this);

    if(m_callbacks[i]->callOnce())
    {
      m_callbacks.erase(m_callbacks.begin() + i);
    }
  }
}