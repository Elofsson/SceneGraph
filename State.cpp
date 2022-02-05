#include "State.h"

//State::State(GLuint program)
//{
  //m_program = program;
//}

State::State()
{

}

void State::setProgram(GLuint program)
{
  m_program = program;
}

void State::setMaterial(std::shared_ptr<Material>& material)
{
  m_material = material;
}

bool State::apply()
{
  m_material->apply(m_program);
  //TODO Call the apply method for Texture, and Light.
  return true;
}

void State::setTextures(TextureVector &texture)
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

void State::setLights(LightVector &light)
{

}

void State::setPolygonMode(GLuint mode)
{

}

void State::setCullFace(bool useCullFace)
{
  
}

bool State::getLocations()
{
  //m_material_ambient_uniform = glGetUniformLocation(m_program, "material.ambient");
  //m_material_specular_uniform = glGetUniformLocation(m_program, "material.specular");
  //m_material_diffuse_uniform = glGetUniformLocation(m_program, "material.diffuse");
  //m_material_shininess_uniform = glGetUniformLocation(m_program, "material.shininess");
}