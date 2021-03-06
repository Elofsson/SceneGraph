#include "Scene.h"
#include <iostream>
#include <vr/shaderUtils.h>
#include "Debug.h"
#include "DotVisitor.h"
#include "SkyBox.h"

Scene::Scene() : m_uniform_numberOfLights(-1)
{
  m_cameras.push_back(std::shared_ptr<Camera>(new Camera));
  m_selectedCamera = DEFAULT_CAMERA;
  m_root = std::shared_ptr<Group>(new Group);
  m_root->name = "Root ";
  m_shadowsEnabled = false;
  m_renderer = std::shared_ptr<RenderVisitor>(new RenderVisitor());
  m_updater = std::shared_ptr<UpdateVisitor>(new UpdateVisitor());
  m_shadowMap = nullptr;
  m_skybox = nullptr;
  m_physics = std::shared_ptr<Physics>(new Physics());
}

Scene::~Scene()
{
  for(auto program : m_programs)
  {
    glDeleteProgram(program);
  }
}

bool Scene::initShadows(const std::string& vshader_filename, const std::string& fshader_filename)
{
  int id = addShader(vshader_filename, fshader_filename);
  if(id == -1)
    return false;

  int width = 1080;
  int height = 1080;
  m_depthProgram = m_programs[id];
  return true;
}

bool Scene::initShaders(const std::string& vshader_filename, const std::string& fshader_filename)
{
  /* Compile and link shaders */
  int id = addShader(vshader_filename, fshader_filename);
  if(id == -1)
    return false;
  
  m_cameras[DEFAULT_CAMERA]->init(m_programs[id]);

  //Set root state.
  std::shared_ptr<State> rootState = std::shared_ptr<State>(new State());
  rootState->setProgram(m_programs[id]);
  rootState->setPolygonMode(GL_FILL);
  rootState->setCullFace(false);
  m_root->setState(rootState);

  //Load physics debug shaders.
  if(!m_physics->init("shaders/debug-physics.vert.glsl", "shaders/debug-physics.frag.glsl"))
  {
    std::cout << "Failed to load physics " << std::endl;
    return false;
  }
  
  return true;
}

int Scene::addShader(const std::string& vshader_filename, const std::string& fshader_filename)
{
  /* Compile and link shaders */
  GLuint program = glCreateProgram();
  GLint link_ok = GL_FALSE;
  GLint validate_ok = GL_FALSE;
  GLuint vs, fs;
  if ((vs = vr::loadShader(vshader_filename, GL_VERTEX_SHADER)) == 0) return false;
  if ((fs = vr::loadShader(fshader_filename, GL_FRAGMENT_SHADER)) == 0) return false;

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    std::cout << "\t linking failed" << std::endl;
    vr::printCompilationError(program);
    return -1;
  }
  glValidateProgram(program);
  glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_ok);
  if (!validate_ok) {
    fprintf(stderr, "glValidateProgram:");
    vr::printCompilationError(program);
    return -1;
  }

  //Add new program and return id to the program.
  m_programs.push_back(program);
  return m_programs.size() - 1;
}

void Scene::add(std::shared_ptr<Light>& light)
{
  m_root->getState()->addLight(light);
}

void Scene::addShadowMap(std::shared_ptr<Light>& light, std::shared_ptr<Camera> camera)
{
  m_shadowMap = std::shared_ptr<ShadowMap>(new ShadowMap(m_depthProgram, camera, light));
  //Init on texture slot 3.
  m_shadowMap->init(3);
  m_shadowsEnabled = true;
}

const std::shared_ptr<Group> Scene::getRoot()
{
  return m_root;
}

const LightVector& Scene::getLights()
{
  return m_root->getState()->getLights();
}

std::vector<GLuint> Scene::getPrograms() const
{
  return m_programs;
}

GLuint Scene::getProgram(int shaderId)
{
  if(m_programs.size() > shaderId && !(shaderId < 0))
  {
    return m_programs[shaderId];
  }

  return m_programs[DEFAULT_SHADER];
}

std::shared_ptr<Camera> Scene::getCamera(int cameraId)
{ 
  //check if such a camera exists.
  if(cameraId < m_cameras.size())
  {
    return m_cameras[cameraId];
  }

  //Otherwise, return default camera
  return m_cameras[DEFAULT_CAMERA];
}

int Scene::addCamera(std::shared_ptr<Camera> camera)
{
  m_cameras.push_back(camera);
  return m_cameras.size() - 1;
}

void Scene::applyCamera()
{
  for(auto program : m_programs)
  {
    std::cout << "Apply camera on program: " << program << std::endl;
    glUseProgram(program);
    m_cameras[m_selectedCamera]->init(program);
    m_cameras[m_selectedCamera]->applyPerspective(program);
  }
}

bool Scene::selectCamera(int cameraId)
{
  //Select the new camera if id exists, otherwise keep using the previous camera.
  if(cameraId < m_cameras.size())
  {
    m_selectedCamera = cameraId;
    applyCamera();
    return true;
  }

  return false;
}

std::shared_ptr<Camera> Scene::getSelectedCamera()
{
  return m_cameras[m_selectedCamera];
}

int Scene::getSelectedCameraId()
{
  return m_selectedCamera;
}

void Scene::useProgram(int programId)
{
  if(m_programs.size() > programId && !(programId < 0))
  {
    glUseProgram(m_programs[programId]);
  }
}

void Scene::createDotFile(std::string fileName)
{
  DotVisitor *dotVisitor = new DotVisitor(fileName);
  dotVisitor->visit(*m_root);
  dotVisitor->close();
  free(dotVisitor);
}

//TODO See if there is another way to init geometries other than initVisitor.
void Scene::add(std::shared_ptr<Group> node, int shape, bool staticType, int shader)
{

  //Set shader in state from default shader.
  //Do not have to set default shader explicitly in the state since this is set as default on the root.
  GLuint programToUse = m_programs[DEFAULT_SHADER];
  if(shader != DEFAULT_SHADER && m_programs.size() > shader && !(shader < 0))
  {
    programToUse = m_programs[shader];

    //Create a new state if there is currently no state set on the node.
    if(node->emptyState())
    {
      std::shared_ptr<State> newState = std::shared_ptr<State>(new State());
      newState->setProgram(programToUse);
      node->setState(newState);
    }

    //Set the program on a already existing state in the node.
    else
    {
      node->getState()->setProgram(programToUse);
    }
  }

  std::cout << "Init with programid: " << shader << " Actual program: " << programToUse << std::endl;

  //Initalize new node with initVisitor.
  glUseProgram(programToUse);
  InitVisitor *initVisitor = new InitVisitor(programToUse);
  initVisitor->visit(*node);

  m_physics->add(node, staticType, shape);

  //Add the new node to root graph.
  free(initVisitor);

  m_root->addChild(node);
  m_root->calculateBoundingBox(glm::mat4(1.0f));
}

void Scene::resetTransform()
{
  //FIXME move reset of transforms to transform.
  //for (auto n : m_nodes)
    //n->resetTransform();
}

BoundingBox Scene::calculateBoundingBox()
{
  return m_root->calculateBoundingBox(glm::mat4(1.0f));
}

void Scene::setSkybox(int programId, std::vector<std::string> textures, std::string modelFile)
{
  GLuint program = getProgram(programId);
  if(program == m_programs[DEFAULT_SHADER])
  {
    std::cout << "Could not find skybox program" << std::endl;
    std::cout << "Make sure to add the shader before setting skybox" << std::endl;
    return;
  }

  m_skybox = std::shared_ptr<SkyBox>(new SkyBox(textures, modelFile.c_str(), program));
}

void Scene::enableShadows(bool enabled)
{
  m_shadowsEnabled = enabled;
  m_shadowMap->clear();
}

bool Scene::shadowsIsEnabled()
{
  return m_shadowsEnabled;
}

std::shared_ptr<Physics> Scene::getPhysicsWorld()
{
  return m_physics;
}

void Scene::update(TimeStep ts)
{
  
  m_updater->visit(*m_root);
  //Update physics here.
  m_physics->update(*m_root);
}

//TODO refactor this to a GBuffer class once a minimal version is working.
bool Scene::initGBuffer(std::shared_ptr<Group> debugObj)
{
  m_gbufferDebugObj = debugObj;

  //TODO pass with and height as parameters somewhere.
  int width = 1024;
  int height = 1024;
  int startSlot = 7;

  //Load geometry pass shader.
  const std::string& vshader_filename = "shaders/geometry-pass.vert.glsl";
  const std::string& fshader_filename = "shaders/geometry-pass.frag.glsl";
  int shader = addShader(vshader_filename, fshader_filename);
  if(shader == -1)
  {
    std::cout << "Failed to load gbuffer shaders " << std::endl;
    return false;
  }

  //Load lightning pass shader
  const std::string& vshader_filename_lightning = "shaders/lightning-pass.vert.glsl";
  const std::string& fshader_filename_lightning = "shaders/lightning-pass.frag.glsl";
  int lightPassShaderId = addShader(vshader_filename_lightning, fshader_filename_lightning);
  if(lightPassShaderId == -1)
  {
    std::cout << "Failed to load gbuffer shaders " << std::endl;
    return false;
  }
  
  m_lightningPassProgram = m_programs[lightPassShaderId];
  m_root->getState()->setProgram(m_lightningPassProgram);

  GLuint gBufferProgram = m_programs[shader];
  std::cout << "Gbuffer program id : " << gBufferProgram << std::endl;

  m_GBuffer = std::shared_ptr<RenderToTexture>(new RenderToTexture(width, height, gBufferProgram));

  //Position color texture.
  std::shared_ptr<Texture> positionBuffer = std::shared_ptr<Texture>(new Texture());
  positionBuffer->initEmpty(width, height, startSlot, GL_TEXTURE_2D, GL_FLOAT, GL_RGB32F, GL_RGBA);
  m_GBuffer->addRenderTarget(positionBuffer);

  //Normal color texture
  std::shared_ptr<Texture> normalBuffer = std::shared_ptr<Texture>(new Texture());
  normalBuffer->initEmpty(width, height, startSlot + 1, GL_TEXTURE_2D, GL_FLOAT, GL_RGB16F, GL_RGBA);
  m_GBuffer->addRenderTarget(normalBuffer);

  //Color + specular buffer.
  std::shared_ptr<Texture> albedoSpecBuffer = std::shared_ptr<Texture>(new Texture());
  albedoSpecBuffer->initEmpty(width, height, startSlot + 2, GL_TEXTURE_2D, GL_UNSIGNED_INT, GL_RGBA, GL_RGBA);
  m_GBuffer->addRenderTarget(albedoSpecBuffer);

  m_GBuffer->init();

  return true;
}

void Scene::debugGBuffer(int width, int height)
{  
  //TODO all of this should be moved to a GBuffer class.
  //Get the render targets and the GBuffer.
  auto gBufferRenderTargets = m_GBuffer->getRenderTargets();
  GLuint gBuffer = m_GBuffer->getFrameBuffer();
  glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);

  GLsizei halfWidth = (GLsizei) width / 4;
  GLsizei halfHeight = (GLsizei) height / 4;
  GLsizei destY = 10;
  GLsizei destX = 0;
  GLsizei offset = 10;

  for(int i = 0; i < gBufferRenderTargets.size(); i++)
  {
    std::shared_ptr<Texture> target = gBufferRenderTargets[i];
    //This works since in RenderToTexture they are added in this order.
    //However this should be done in a more clear way.
    glReadBuffer(GL_COLOR_ATTACHMENT0 + i);  
    glBlitFramebuffer(0, 0, halfWidth, halfHeight, destX + offset, destY, destX + halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    destX += halfWidth;
  }

}

void Scene::render()
{

  //Render shadows
  /*if(m_shadowMap != nullptr && m_shadowsEnabled)
  { 
    m_shadowMap->update();
    //Apply shadowmaps on all programs except the depthProgram.
    for(auto program : m_programs)
    {
      //Do not apply with the depthProgram itself.
      if(program != m_depthProgram)
      {
        //std::cout << "Applying shadowmap for program: " << program << std::endl;
        //TODO split current apply method to one render, and one apply.
        m_shadowMap->apply(program, m_root);
      }
    }
  }*/

  //TODO move this GBuffer related things to a GBuffer class
  //glDepthMask(GL_TRUE);

  //glEnable(GL_DEPTH_TEST);

  m_GBuffer->render(getSelectedCamera(), m_root);

  //glDepthMask(GL_FALSE);

  //glDisable(GL_DEPTH_TEST);

  //TODO this is rly bad. Make it more readable
  std::shared_ptr<Texture> positionTexture = m_GBuffer->getRenderTargets()[0];
  std::shared_ptr<Texture> normalTexture = m_GBuffer->getRenderTargets()[1];
  std::shared_ptr<Texture> albedoTexture = m_GBuffer->getRenderTargets()[2];
  
  applyCamera();

  glUseProgram(m_lightningPassProgram);

  const char *uniform = "gPosition";
  positionTexture->apply(m_lightningPassProgram, uniform);

  uniform = "gNormal";
  normalTexture->apply(m_lightningPassProgram, uniform);

  uniform = "gAlbedoSpec";
  albedoTexture->apply(m_lightningPassProgram, uniform);

  //glEnable(GL_BLEND);
  //glBlendEquation(GL_FUNC_ADD);
  //glBlendFunc(GL_ONE, GL_ONE);
  //glClear(GL_COLOR_BUFFER_BIT);

  //Currently force just to test.
  //m_renderer->forceProgram(true, m_lightningPassProgram);
  m_renderer->visit(*m_root); 

  if(m_skybox != nullptr)
  { 
    //Apply selected camera with the skybox program.
    GLuint skyboxProgram = m_skybox->getProgram();
    glUseProgram(skyboxProgram);
    m_cameras[m_selectedCamera]->applyPerspective(skyboxProgram);
    m_skybox->render();
  }

  //Draw collision boxes if debug is enabled.
  if(m_physics->debugEnabled())
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_physics->renderCollisionBoxes(m_cameras[m_selectedCamera]);
    glPolygonMode(GL_FRONT_AND_BACK, m_root->getState()->getPolygonMode());
  }
}
