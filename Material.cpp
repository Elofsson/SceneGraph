/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>

#include "Material.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "Debug.h"

#include <vr/glErrorUtil.h>
#include <sstream>


/// Simple class for storing material properties
Material::Material()
{
  m_epsilon = std::numeric_limits<float>::epsilon();
  m_ambient = glm::vec4(0.1, 1.0, 0.2, 1.0);
  m_diffuse = glm::vec4(0.7, 0.8, 0.8, 1.0);
  m_specular = glm::vec4(1.0, 1.0, 1.0, 1.0);
  m_shininess = 32.0f;
}

glm::vec4 Material::getAmbient() const { return m_ambient; }
glm::vec4 Material::getSpecular() const { return m_specular; }
glm::vec4 Material::getDiffuse() const { return m_diffuse; }
float Material::getShininess() const { return m_shininess; }

void Material::setAmbient(const glm::vec4& color)  { m_ambient = color; }
void Material::setSpecular(const glm::vec4& color)  { m_specular = color; }
void Material::setDiffuse(const glm::vec4& color)  { m_diffuse = color; }
void Material::setShininess(float s)  { m_shininess = s; }

void Material::apply(GLuint program)
{
  GLint loc = 0;
  int i = 0;

  loc = glGetUniformLocation(program, "material.ambient");
  glUniform4fv(loc, 1, glm::value_ptr(m_ambient));

  loc = glGetUniformLocation(program, "material.specular");
  glUniform4fv(loc, 1, glm::value_ptr(m_specular));

  loc = glGetUniformLocation(program, "material.diffuse");
  glUniform4fv(loc, 1, glm::value_ptr(m_diffuse));

  loc = glGetUniformLocation(program, "material.shininess");
  glUniform1f(loc, m_shininess);
}

void Material::merge(std::shared_ptr<Material> material)
{
  if(!VectorUtils::compareVec4(material->getAmbient(), m_ambient))
  {
    m_ambient = material->getAmbient();
  }

  if(!VectorUtils::compareVec4(material->getDiffuse(), m_diffuse))
  {
    m_diffuse = material->getDiffuse();
  }

  if(!VectorUtils::compareVec4(material->getSpecular(), m_specular))
  {
    m_specular = material->getSpecular();
  }

  float shininessDiff = std::fabs(m_shininess - material->getShininess());
  if(shininessDiff > m_epsilon)
  {
    m_shininess = material->getShininess();
  }
}