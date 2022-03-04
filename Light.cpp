#include "Light.h"
#include "Geometry.h"
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Light::Light() : m_enabled(true)
{
}

void Light::apply(GLuint program, size_t idx)
{
  int i = 0;
  std::stringstream str;
  str << "lights[" << idx << "].";
  std::string prefix = str.str();

  GLint loc = -1;
  std::string uniform_name;

  uniform_name = prefix + "enabled";
  loc = glGetUniformLocation(program, uniform_name.c_str());
  if (loc == -1) {
    //std::cerr << "Could not bind uniform << " << uniform_name << std::endl;
    return;
  }
  glUniform1i(loc, m_enabled);

#define APPLY_UNIFORM4V(PROGRAM, NAME, VALUE) \
    uniform_name = prefix + std::string(NAME);  \
    loc = glGetUniformLocation(program, uniform_name.c_str()); \
    if (loc == -1) { \
      std::cerr << "Could not bind uniform << " << uniform_name << std::endl; \
      return; \
            } \
    glUniform4fv(loc, 1, glm::value_ptr(VALUE));

  //TODO make ambient work.
  APPLY_UNIFORM4V(program, "diffuse", this->m_diffuse);
  APPLY_UNIFORM4V(program, "specular", this->m_specular);
  APPLY_UNIFORM4V(program, "position", this->m_position);
}

bool Light::equals(std::shared_ptr<Light> light)
{
  if(!VectorUtils::compareVec4(m_ambient, light->getAmbient()))
  {
    return false;
  }

  if(!VectorUtils::compareVec4(m_diffuse, light->getDiffuse()))
  {
    return false;
  }

  if(!VectorUtils::compareVec4(m_specular, light->getSpecular()))
  {
    return false;
  }

  if(!VectorUtils::compareVec4(m_position, light->getPosition()))
  {
    return false;
  }

  return true;
}

//Setters.
void Light::setAmbient(glm::vec4 ambient) { m_ambient = ambient; }
void Light::setDiffuse(glm::vec4 diffuse) { m_diffuse = diffuse; }
void Light::setSpecular(glm::vec4 specular) { m_specular = specular; }
void Light::setPosition(glm::vec4 position) { m_position = position; }
void Light::setEnabled(bool enabled) { m_enabled = enabled; }


//Getters.
glm::vec4 Light::getAmbient() { return m_ambient; }
glm::vec4 Light::getDiffuse() { return m_diffuse; }
glm::vec4 Light::getSpecular() { return m_specular; }
glm::vec4 Light::getPosition() { return m_position; }
bool Light::isEnabled() { return m_enabled; }