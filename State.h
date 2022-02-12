#pragma once

#include "Texture.h"
#include "Material.h"
#include "glm/gtc/type_ptr.hpp"
#include "Light.h"

#define SHADER_NUMBER_TEXTURES 2

class Light;

class State
{

public:
  State();
  State(std::shared_ptr<State> state);

  //Setters.
  void setMaterial(std::shared_ptr<Material> &material);
  void addTexture(std::shared_ptr<Texture> &texture, unsigned int unit);
  void setTextures(TextureVector &textures);
  void addLight(std::shared_ptr<Light> &light);
  void setPolygonMode(GLuint mode);
  void setCullFace(bool useCullFace);
  void setProgram(GLuint Program);

  //Getters.
  std::shared_ptr<Material>& getMaterial();
  TextureVector& getTextures();
  LightVector& getLights();
  GLuint getPolygonMode();
  bool getCullFaceMode();
  GLuint getProgram();

  void merge(const std::shared_ptr<State> state);

  bool apply();
  
  void unbindTextures();

private:
  //Retrieve uniform locations.
  bool getLocations();

  //Help methods to merge states.
  void updateLights(LightVector inputLights);

  bool m_backface_culling;
  GLuint m_program;
  GLuint m_polygonmode;
  GLuint m_uniform_numberOfLights;

  TextureVector m_textures;
  LightVector m_lights;
  //Material.
  std::shared_ptr<Material> m_material;

};