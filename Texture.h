#pragma once

#include "GL/glew.h"
#include <vector>
#include <memory>

//TODO Should contain textures to be applied to surfaces.
//TODO Method to apply texture.

class Texture
{
public:
  Texture();
  bool init(const char *image, unsigned int slot, GLenum texType, GLenum pixelType);
  void apply(GLuint program);
  void bind();
  void unbind();

private:
  unsigned char* readTexture(std::string filePath, int *width, int *height, int *numChannels);

  GLuint m_texture_id;
  GLuint m_type;
  unsigned int m_slot;
};

typedef std::vector<std::shared_ptr<Texture>> TextureVector;