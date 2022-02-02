#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Mesh.h"
#include <vector>

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
  std::shared_ptr<Mesh> m_mesh;

  void createMesh();
  std::shared_ptr<Mesh>& getMesh();
  void apply(GLuint program, size_t idx);
};
typedef std::vector<std::shared_ptr<Light> > LightVector;


