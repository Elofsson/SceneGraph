#include "State.h"
#include <iostream>
//State::State(GLuint program)
//{
  //m_program = program;
//}

State::State()
{
  m_lights.resize(0);
  m_textures.resize(0);
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
  getLocations();

  //Apply materials.
  if(m_material)
    m_material->apply(m_program);

  //Apply textures.
  if(!m_textures.empty())
  {
    for(auto texture : m_textures)
    {
      std::cout << "Apply texture" << std::endl;
      texture->apply(m_program);
    }

  }

  //Apply lights.
  if(!m_lights.empty())
  {
    //Update number of lights
    glUniform1i(m_uniform_numberOfLights, (GLint)m_lights.size());

    size_t i = 0;
    for (auto l : m_lights)
    {
      //std::cout << "Apply light[" << i << "]" << std::endl;
      l->apply(m_program, i++);
    }
  }

  //TODO Call the apply method for Texture, and Light.
  return true;
}

void State::setTextures(TextureVector &textures)
{
  m_textures = textures;
}

void State::addLight(std::shared_ptr<Light> &light)
{
  m_lights.push_back(light);
}

void State::setPolygonMode(GLuint mode)
{

}

void State::setCullFace(bool useCullFace)
{
  
}

bool State::getLocations()
{
  const char *uniform_name = "numberOfLights";
  m_uniform_numberOfLights = glGetUniformLocation(m_program, uniform_name);
  if (m_uniform_numberOfLights == -1) {
    std::cerr << "Could not bind uniform " << uniform_name << std::endl;
  }
  //m_material_ambient_uniform = glGetUniformLocation(m_program, "material.ambient");
  //m_material_specular_uniform = glGetUniformLocation(m_program, "material.specular");
  //m_material_diffuse_uniform = glGetUniformLocation(m_program, "material.diffuse");
  //m_material_shininess_uniform = glGetUniformLocation(m_program, "material.shininess");
}