#include "State.h"
#include <iostream>
#include "Debug.h"
#include <vr/glErrorUtil.h>

State::State()
{
  m_lights.resize(0);
  m_textures.resize(2);
  m_material = std::shared_ptr<Material>(new Material());
  m_polygonmode = -1;
  m_program = 0;
}

State::State(std::shared_ptr<State> state)
{
  m_lights = state->getLights();
  m_textures = state->getTextures();
  if(state->getMaterial() != nullptr)
  {
    m_material = std::shared_ptr<Material>(new Material(state->getMaterial()));
  }
  m_polygonmode = state->getPolygonMode();
  m_backface_culling = state->getCullFaceMode();
  m_program = state->getProgram();
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

  TextureVector inputTextures = inputState->getTextures();
  if(!inputTextures.empty())
  {
    for(unsigned int i = 0; i < inputTextures.size(); i++)
    {
      addTexture(inputTextures[i], i);
    }
  }

  //Update culling mode
  if(m_backface_culling != inputState->getCullFaceMode())
  {
    //std::cout << "Update state culling " << std::endl;
    m_backface_culling = inputState->getCullFaceMode();
  }

  //Update polygonmode
  if(inputState->getPolygonMode() != -1)
  {
    m_polygonmode = inputState->getPolygonMode();
  }

  //Update program
  if(inputState->getProgram() != 0)
  {
    //std::cout << "Update state program" << std::endl; 
    m_program = inputState->getProgram();
  }
}

void State::updateLights(LightVector inputLights)
{
  for(auto newLight : inputLights)
  {   
    bool addNewLight = true;
    for(auto light : m_lights)
    {
      if(light->equals(newLight))
      {
        addNewLight = false;
      }
    }

    if(addNewLight)
    {
      m_lights.push_back(newLight);
    }
  }
}

bool State::apply()
{
  //std::cout << "Program in state: " << m_program << std::endl;
  glUseProgram(m_program);
  getLocations();

  //Apply materials.
  if(m_material)
    m_material->apply(m_program);

  std::vector<int> slotActive;
  slotActive.resize(m_textures.size());

  for(int i = 0; i < m_textures.size(); i++)
  {
    slotActive[i] = m_textures[i] != nullptr;

    if(slotActive[i])
    {
      std::string uniform = "material.textures[";
	    uniform.append(std::to_string(i));
	    uniform.append("]");
      m_textures[i]->apply(m_program, uniform);
    }
  }

  GLuint loc = glGetUniformLocation(m_program, "material.activeTextures");
  glUniform1iv(loc, (GLsizei)slotActive.size(), slotActive.data());


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

  //Apply polygonmode
  if(m_polygonmode != -1)
  {
    glPolygonMode(GL_BACK, m_polygonmode);
  }

  else
  {
    glPolygonMode(GL_BACK, GL_FILL);
  }
    
  return true;
}

void State::addTexture(std::shared_ptr<Texture> &texture, unsigned int unit)
{
  m_textures[unit] = texture;
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
  glPolygonMode(GL_BACK, m_polygonmode);
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


void State::unbind()
{
  glUseProgram(0);

  for(auto texture : m_textures)
  {
    if(texture != nullptr)
    {
      texture->unbind();
    }
  }
}

  //Getters.
  std::shared_ptr<Material>& State::getMaterial() { return m_material; }
  TextureVector& State::getTextures() { return m_textures; }
  LightVector& State::getLights() { return m_lights; }
  GLuint State::getPolygonMode() { return m_polygonmode; }
  bool State::getCullFaceMode() { return m_backface_culling; }
  GLuint State::getProgram() { return m_program; }