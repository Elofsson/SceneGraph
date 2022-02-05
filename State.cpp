#include "State.h"

State::State(GLuint program)
{
  m_program = program;

  getLocations();
}

void State::apply(Material &material)
{
  glUniform4fv(m_material_ambient_uniform, 1, glm::value_ptr(material.getAmbient()));
  glUniform4fv(m_material_specular_uniform, 1, glm::value_ptr(material.getSpecular()));
  glUniform4fv(m_material_diffuse_uniform, 1, glm::value_ptr(material.getDiffuse()));
  glUniform1f(m_material_shininess_uniform, material.getShininess());
}

void State::apply(Texture &texture)
{
  //FIXME fix textures.
  /*std::vector<int> slotActive;
  std::vector<int> slots;
  slotActive.resize(m_textures.size());
  slots.resize(m_textures.size());
  for (int i = 0; i < m_textures.size(); i++)
  {
    slots[i] = i;
    slotActive[i] = m_textures[i] != nullptr;
    if (m_textures[i])
      m_textures[i]->bind();
  }*/
}

void State::apply(Light &light)
{

}

void State::applyPolygonMode(GLuint mode)
{

}

void State::applyCullFace(bool useCullFace)
{
  
}

bool State::getLocations()
{
  m_material_ambient_uniform = glGetUniformLocation(m_program, "material.ambient");
  m_material_specular_uniform = glGetUniformLocation(m_program, "material.specular");
  m_material_diffuse_uniform = glGetUniformLocation(m_program, "material.diffuse");
  m_material_shininess_uniform = glGetUniformLocation(m_program, "material.shininess");
}