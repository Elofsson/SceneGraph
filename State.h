#pragma once

#include "Light.h"
#include "Texture.h"
#include "Material.h"
#include "glm/gtc/type_ptr.hpp"

class State
{

public:
  State(GLuint program);
  void apply(Material &material);
  void apply(Texture &texture);
  void apply(Light &light);
  void applyPolygonMode(GLuint mode);
  void applyCullFace(bool useCullFace);
  //TODO add method to apply new shaders here.

private:
  //Retrieve uniform locations.
  bool getLocations();

  GLuint m_program;

  //Material.
  GLuint m_material_ambient_uniform;
  GLuint m_material_diffuse_uniform;
  GLuint m_material_specular_uniform;
  GLuint m_material_shininess_uniform;

};