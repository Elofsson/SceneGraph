#include "State.h"
#include <iostream>
#include "Debug.h"
#include <vr/glErrorUtil.h>
//State::State(GLuint program)
//{
  //m_program = program;
//}

State::State()
{
  m_lights.resize(0);
  m_textures.resize(0);
  m_material = std::shared_ptr<Material>(new Material());
}

void State::setProgram(GLuint program)
{
  m_program = program;
}

void State::setMaterial(std::shared_ptr<Material>& material)
{
  m_material = material;
}

void State::merge(const std::shared_ptr<State> inputState)
{

  if(inputState == NULL)
  {
    return;
  }

  //Update material.
  std::shared_ptr<Material> inputMaterial = inputState->getMaterial();

  //Input material seems to be changed to last value.
  if(inputMaterial != NULL)
  {
    m_material->merge(inputMaterial);
  }

  //Update lights.
  LightVector inputLights = inputState->getLights();
  if(!inputLights.empty())
  {
    updateLights(inputLights);
  }

  //TODO Update textures here.
  TextureVector inputTextures = inputState->getTextures();
  if(!inputTextures.empty())
  {
    m_textures.clear();
    m_textures = inputTextures;
  }

  //Update culling mode
  if(m_backface_culling != inputState->getCullFaceMode())
  {
    //std::cout << "Update state culling " << std::endl;
    m_backface_culling = inputState->getCullFaceMode();
  }

  //Update polygonmode
  if(m_polygonmode != inputState->getPolygonMode())
  {
    //std::cout << "Update state polygonmode" << std::endl;
    m_polygonmode = inputState->getPolygonMode();
  }

  //Update program
  if(m_program != inputState->getProgram())
  {
    //std::cout << "Update state program" << std::endl; 
    m_program = inputState->getProgram();
  }
}

void State::updateLights(LightVector inputLights)
{
  //std::cout << "Update state lights" << std::endl;
  if(m_lights.empty())
  {
    for(auto light : inputLights)
    {
      m_lights.push_back(light);
    }
    return;
  }

  for(auto inputLight : inputLights)
  {
    glm::vec4 inputLightAmbient = inputLight->getAmbient(); 
    glm::vec4 inputLightDiffuse = inputLight->getDiffuse();
    glm::vec4 inputLightSpecular = inputLight->getSpecular();
    glm::vec4 inputLightPosition = inputLight->getPosition();

    for(auto light : m_lights)
    {
      if(light->getAmbient() != inputLightAmbient)
      {
        light->setAmbient(inputLightAmbient);
      }

      if(light->getDiffuse() != inputLightDiffuse)
      {
        light->setDiffuse(inputLightDiffuse);
      }

      if(light->getSpecular() != inputLightSpecular)
      {
        light->setSpecular(inputLightSpecular);
      }

      if(light->getPosition() != inputLightPosition)
      {
        light->setPosition(inputLightPosition);
      }
    }
  }
}

bool State::apply()
{
  getLocations();

  //Apply materials.
  if(m_material)
    m_material->apply(m_program);

  std::vector<int> slotActive;
  //Apply textures.
  if(!m_textures.empty())
  {
    for(int i = 0; i < SHADER_NUMBER_TEXTURES; i++)
    {
      if(m_textures.size() > i)
      {
        std::shared_ptr<Texture> texture = m_textures[i];
        texture->apply(m_program);
        //std::cout << "Apply texture " << i << std::endl;
        slotActive.push_back((int) true);  
      }

      else 
      {
        //std::cout << "Add inactive" << std::endl;
        slotActive.push_back((int) false);    
      }
    }

    GLuint loc = glGetUniformLocation(m_program, "material.activeTextures");
    glUniform1iv(loc, (GLsizei)slotActive.size(), slotActive.data());
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

  return true;
}

void State::addTexture(std::shared_ptr<Texture> &texture)
{
  m_textures.push_back(texture);
}

void State::addLight(std::shared_ptr<Light> &light)
{
  m_lights.push_back(light);
}

void State::setPolygonMode(GLuint mode)
{
  if(mode != GL_FILL && mode != GL_POINT && mode != GL_LINE)
  {
    std::cerr << "Nonsupported polygon mode" << std::endl;
    return;
  }
  
  std::cout << "Update polygonmode" << std::endl;
  m_polygonmode = mode;
  glPolygonMode(GL_FRONT_AND_BACK, m_polygonmode);
}

void State::setCullFace(bool useCullFace)
{
  if(useCullFace)
  {
    std::cout << "Enable culling of backfaces" << std::endl;
    glEnable(GL_CULL_FACE);
  } 
  else
  {
    std::cout << "Disable culling of backfaces" << std::endl;
    glDisable(GL_CULL_FACE);
  }

  m_backface_culling = useCullFace;
}

bool State::getLocations()
{
  const char *uniform_name = "numberOfLights";
  m_uniform_numberOfLights = glGetUniformLocation(m_program, uniform_name);
  if (m_uniform_numberOfLights == -1) {
    std::cerr << "Could not bind uniform " << uniform_name << std::endl;
    return false;
  }
  //m_material_ambient_uniform = glGetUniformLocation(m_program, "material.ambient");
  //m_material_specular_uniform = glGetUniformLocation(m_program, "material.specular");
  //m_material_diffuse_uniform = glGetUniformLocation(m_program, "material.diffuse");
  //m_material_shininess_uniform = glGetUniformLocation(m_program, "material.shininess");
  return true;
}


void State::unbindTextures()
{
  for(auto texture : m_textures)
  {
    texture->unbind();
  }
}

  //Getters.
  std::shared_ptr<Material>& State::getMaterial() { return m_material; }
  TextureVector& State::getTextures() { return m_textures; }
  LightVector& State::getLights() { return m_lights; }
  GLuint State::getPolygonMode() { return m_polygonmode; }
  bool State::getCullFaceMode() { return m_backface_culling; }
  GLuint State::getProgram() { return m_program; }