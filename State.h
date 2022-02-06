#pragma once

#include "Texture.h"
#include "Material.h"
#include "glm/gtc/type_ptr.hpp"
#include "Light.h"

class Light;

class State
{

public:
  State();
  void setMaterial(std::shared_ptr<Material>& material);
  void setTextures(TextureVector &textures);
  void addLight(std::shared_ptr<Light> &light);
  void setPolygonMode(GLuint mode);
  void setCullFace(bool useCullFace);
  void setProgram(GLuint Program);
  void initalize(GLuint program);

  bool apply();
  //TODO add method to apply new shaders here.

private:
  //Retrieve uniform locations.
  bool getLocations();

  GLuint m_program;
  GLuint m_polygonmode;
  GLuint m_uniform_numberOfLights;

  TextureVector m_textures;
  LightVector m_lights;
  //Material.
  std::shared_ptr<Material> m_material;

};