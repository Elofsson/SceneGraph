#include "SkyBox.h"

SkyBox::SkyBox(std::vector<std::string> textures, const char *objFilePath, GLuint skyboxProgram) {
    //shader = new Shader("./src/shader/shaders/skybox/vsbshader.glsl", "./src/shader/shaders/skybox/fsbshader.glsl");
    //shader->use();
    m_skyboxTexture = std::shared_ptr<Texture>(new Texture());
    m_renderer = std::shared_ptr<RenderVisitor>(new RenderVisitor());
    m_program = skyboxProgram;


    loadCubemap(textures);    //Load with multiple images.
    initSkybox(objFilePath);
    std::cout << "Skybox initalized" << std::endl;
}

SkyBox::~SkyBox() 
{
}

void SkyBox::initSkybox(const char *objFilePath) {
  //Read skybox model.
  m_skyboxObject = load3DModelFile(objFilePath);
  InitVisitor *initVisitor = new InitVisitor(m_program);
  initVisitor->visit(*m_skyboxObject);
  free(initVisitor);

  //Set state.
  std::shared_ptr<State> newState = std::shared_ptr<State>(new State);
  newState->setProgram(m_program);
  m_skyboxObject->setState(newState);
}

void SkyBox::loadCubemap(std::vector<std::string> textures) { 
  //TODO pass slot here somehow?
  if(!m_skyboxTexture->initCubemap(textures, 6, GL_TEXTURE_CUBE_MAP, GL_UNSIGNED_BYTE))
  {
    std::cout << "Failed to load cubemap" << std::endl;
    return;
  }
}

void SkyBox::render() {
  glDepthFunc(GL_LEQUAL); 

  std::string uniform = "skybox";
  m_skyboxTexture->bind();
  m_skyboxTexture->apply(m_program, uniform);
  m_renderer->visit(*m_skyboxObject);
  
  glDepthFunc(GL_LESS);
}


GLuint SkyBox::getProgram()
{
  return m_program;
}