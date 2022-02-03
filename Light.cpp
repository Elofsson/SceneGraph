#include "Light.h"
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Light::Light() : enabled(true)
{
  createGeometry();
}


void Light::createGeometry()
{
  m_geometry = std::shared_ptr<Geometry>(new Geometry());

  float size = 0.1f;
  glm::vec3 light_position = glm::vec3(0.0, 1.0, 2.0);
  m_geometry->vertices.push_back(glm::vec4(-size, -size, -size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(size, -size, -size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(size, size, -size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(-size, size, -size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(-size, -size, size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(size, -size, size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(size, size, size, 0.0));
  m_geometry->vertices.push_back(glm::vec4(-size, size, size, 0.0));
  //TODO check what to do with this matrix
  //m_geometry->object2world = glm::translate(glm::mat4(1), glm::vec3(this->position));
  m_geometry->name = "light";
}

std::shared_ptr<Geometry>& Light::getGeometry() 
{ 
  return m_geometry; 
}

/*void Light::apply(GLuint program, size_t idx)
{
  int i = 0;

  // Update light position
  m_mesh->object2world = glm::translate(glm::mat4(1), glm::vec3(this->position));

  std::stringstream str;
  str << "lights[" << idx << "].";
  std::string prefix = str.str();

  GLint loc = -1;
  std::string uniform_name;

  uniform_name = prefix + "enabled";
  loc = glGetUniformLocation(program, uniform_name.c_str());
  if (loc == -1) {
    std::cerr << "Could not bind uniform << " << uniform_name << std::endl;
    return;
  }
  glUniform1i(loc, enabled);

#define APPLY_UNIFORM4V(PROGRAM, NAME, VALUE) \
    uniform_name = prefix + std::string(NAME);  \
    loc = glGetUniformLocation(program, uniform_name.c_str()); \
    if (loc == -1) { \
      std::cerr << "Could not bind uniform << " << uniform_name << std::endl; \
      return; \
            } \
    glUniform4fv(loc, 1, glm::value_ptr(VALUE));

  APPLY_UNIFORM4V(program, "diffuse", this->diffuse);
  APPLY_UNIFORM4V(program, "specular", this->specular);
  APPLY_UNIFORM4V(program, "position", this->position);
}*/
