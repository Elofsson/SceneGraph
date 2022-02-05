/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>

#include "Material.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include <vr/glErrorUtil.h>
#include <sstream>


/// Simple class for storing material properties
Material::Material() : m_shininess(5)
{
  m_ambient = glm::vec4(0.1, 1.0, 0.2, 1.0);
  m_diffuse = glm::vec4(0.7, 0.8, 0.8, 1.0);
  m_specular = glm::vec4(1.0, 1.0, 1.0, 1.0);

  //m_textures.resize(2);
}

glm::vec4 Material::getAmbient() const { return m_ambient; }
glm::vec4 Material::getSpecular() const { return m_specular; }
glm::vec4 Material::getDiffuse() const { return m_diffuse; }
float Material::getShininess() const { return m_shininess; }

void Material::setAmbient(const glm::vec4& color)  { m_ambient = color; }
void Material::setSpecular(const glm::vec4& color)  { m_specular = color; }
void Material::setDiffuse(const glm::vec4& color)  { m_diffuse = color; }
void Material::setShininess(float s)  { m_shininess = s; }

/*void Material::apply(State state)
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

  std::vector<int> slotActive;
  std::vector<int> slots;
  slotActive.resize(m_textures.size());
  slots.resize(m_textures.size());
  for (int i = 0; i < m_textures.size(); i++)
  {
    slots[i] = i;
    slotActive[i] = m_textures[i] != nullptr;
    if (m_textures[i])
      m_textures[i]->bind();
  }

  loc = glGetUniformLocation(program, "material.textures");
  glUniform1iv(loc, (GLsizei)slots.size(), slots.data());

  CHECK_GL_ERROR_LINE_FILE();

  loc = glGetUniformLocation(program, "material.activeTextures");
  glUniform1iv(loc, (GLsizei)slotActive.size(), slotActive.data());

  CHECK_GL_ERROR_LINE_FILE();
}

void Material::setTexture(std::shared_ptr<vr::Texture> texture, unsigned int unit)
{
  m_textures[unit] = texture;
}*/
