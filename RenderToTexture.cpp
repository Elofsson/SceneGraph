#include "RenderToTexture.h"


RenderToTexture::RenderToTexture(unsigned int width, unsigned int height, GLuint program)
{
  m_program = program;
  m_renderer = std::shared_ptr<RenderVisitor>(new RenderVisitor());
  m_width = width;
  m_height = height;
  m_texture = std::shared_ptr<Texture>(new Texture());
}

bool RenderToTexture::init(unsigned int textureSlot)
{
  m_texture->initEmpty(m_width, m_height, textureSlot, GL_TEXTURE_2D, GL_FLOAT);
  m_texture->bind();

  // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  glGenFramebuffers(1, &m_framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

  //Set our texture.
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_texture->getTextureId(), 0);

  //Configure draw buffers to use no colors.
  glDrawBuffer(GL_NONE);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    std::cout << "Failed to create RenderToTexture" << std::endl;
    return false;
  }

  return true;
}

//TODO find a way to reset viewport.
void RenderToTexture::render(std::shared_ptr<Camera> camera, std::shared_ptr<Group> startNode)
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
  glViewport(0,0,m_width, m_height);
  glCullFace(GL_FRONT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(m_program); 

  //Apply camera.
  camera->init(m_program);
  camera->applyOrthogonal(m_program, startNode->getBoundingBox());

  //Set program on node.
  GLuint previousProgram = -1;
  if(!startNode->emptyState())
  {
    previousProgram = startNode->getState()->getProgram();
    startNode->getState()->setProgram(m_program);
  }

  //If no state is set on the given node, create one containing this class program.
  else
  {
    std::shared_ptr<State> state = std::shared_ptr<State>(new State());
    state->setProgram(m_program);
    startNode->setState(state);
  }

  bool previousCullMode = startNode->getState()->getCullFaceMode();
  startNode->getState()->setCullFace(true); //Enable culling.

  //Use rendervisitor here.
  m_renderer->visit(*startNode);

  //After texture is done rendering, reset state to previous state.
  if(previousProgram != -1)
  {
    startNode->getState()->setProgram(previousProgram);
  }
  
  startNode->getState()->setCullFace(previousCullMode);
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glm::vec2 screenSize = camera->getScreenSize();
  glViewport(0,0,screenSize.x, screenSize.y);
  glCullFace(GL_BACK);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//TODO find another way to init this program.
GLuint RenderToTexture::getProgram()
{
  return m_program;
}

std::shared_ptr<Texture> RenderToTexture::getTexture()
{
  return m_texture;
}