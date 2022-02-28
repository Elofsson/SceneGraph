#pragma once

#include "GL/glew.h"
#include <vector>
#include <memory>
#include <string>

//TODO Should contain textures to be applied to surfaces.
//TODO Method to apply texture.

class Texture
{
public:
  Texture();
  bool init(const char *image, unsigned int slot, GLenum texType, GLenum pixelType);
  bool initCubemap(std::vector<std::string> textures, unsigned int slot, GLenum texType, GLenum pixelType);
  void initEmpty(unsigned int width, unsigned int height, unsigned int slot, GLenum texType, GLenum pixelType);
  void initData(unsigned int width, unsigned int height, unsigned int slot, GLenum texType, GLenum pixelType, unsigned char *data);
  void apply(GLuint program, std::string uniform);
  void setWrapSetting(GLuint wrapSetting);
  void setFilterSetting(GLuint filterSetting);
  void bind();
  void unbind();
  GLuint getTextureId();

private:
  std::string getFilePath(const char *image);
  void setupTexture();
  void cleanupInit(unsigned char *bytes);
  
  unsigned char* readTexture(std::string filePath, int *width, int *height, int *numChannels);

  GLuint m_texture_id;
  GLuint m_type;
  unsigned int m_slot;
};

typedef std::vector<std::shared_ptr<Texture>> TextureVector;