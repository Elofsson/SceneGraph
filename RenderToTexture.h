#pragma once

#include "GL/glew.h"
#include "Camera.h"
#include "RenderVisitor.h"

class RenderToTexture
{

public:
  RenderToTexture(unsigned int width, unsigned int height, GLuint program);
  void render(std::shared_ptr<Camera> camera, std::shared_ptr<Group> startNode);
  void addRenderTarget(std::shared_ptr<Texture> target);
  void clear();
  bool init(unsigned int textureSlot);
  bool init();
  GLuint getProgram();
  std::shared_ptr<Texture> getTexture();
  std::vector<std::shared_ptr<Texture>> getRenderTargets();
  GLuint getFrameBuffer();

private:
  std::vector<GLenum> m_drawBufferAttachments;
  std::vector<std::shared_ptr<Texture>> m_renderTargets;
  
  GLuint m_framebuffer;
  GLuint m_program;
  unsigned int m_width;
  unsigned int m_height;
  std::shared_ptr<Texture> m_texture;
  std::shared_ptr<RenderVisitor> m_renderer;
};