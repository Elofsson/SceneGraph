#pragma once

#include <glm/glm.hpp>
#include "GL/glew.h"
#include <memory>
#include <vector>

class Geometry;

/// Simple class that store light properties and apply them to Uniforms
class Light
{
public:
  bool enabled;
  glm::vec4 position;
  glm::vec4 diffuse;
  glm::vec4 specular;

  Light();

private:
  friend class Scene;
  std::shared_ptr<Geometry> m_geometry;

  void createGeometry();
  std::shared_ptr<Geometry>& getGeometry();
  
  //TODO check where to put this.
  void apply(GLuint program, size_t idx);
};
typedef std::vector<std::shared_ptr<Light>> LightVector;


