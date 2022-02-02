#pragma once

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
/* GLM */
// #define GLM_MESSAGES
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <vr/Texture.h>

/// <summary>
/// Simple class for storing material properties
/// </summary>
class Material
{
private:

  glm::vec4 m_ambient, m_diffuse, m_specular;

  GLfloat m_shininess;

  typedef std::vector<std::shared_ptr<vr::Texture> > TextureVector;
  TextureVector m_textures;

public:

  Material();

  glm::vec4 getAmbient() const;
  glm::vec4 getSpecular() const;
  glm::vec4 getDiffuse() const;

  void setAmbient(const glm::vec4& color);
  void setSpecular(const glm::vec4& color);
  void setDiffuse(const glm::vec4& color);
  void setShininess(float s);

  void setTexture(std::shared_ptr<vr::Texture> texture, unsigned int unit);

  void apply(GLuint program);


};

typedef std::vector<std::shared_ptr<Material> > MaterialVector;

