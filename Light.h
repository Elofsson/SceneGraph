#pragma once

#include <glm/glm.hpp>
#include "GL/glew.h"
#include <memory>
#include <vector>
#include "VectorUtils.h"

class Geometry;

/// Simple class that store light properties and apply them to Uniforms
class Light
{
public:
  Light();

  
  bool equals(std::shared_ptr<Light> light);

  void apply(GLuint program, size_t idx);

  glm::vec4 getAmbient();
  glm::vec4 getDiffuse();
  glm::vec4 getSpecular();
  glm::vec4 getPosition();
  bool isEnabled();

  void setAmbient(glm::vec4 ambient);
  void setDiffuse(glm::vec4 diffuse);
  void setSpecular(glm::vec4 specular);
  void setPosition(glm::vec4 position);
  void setEnabled(bool enabled);

private:

  bool m_enabled;
  glm::vec4 m_position;
  glm::vec4 m_diffuse;
  glm::vec4 m_specular;
  glm::vec4 m_ambient;
};
typedef std::vector<std::shared_ptr<Light>> LightVector;


