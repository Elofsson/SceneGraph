#include "Scene.h"
#include <iostream>
#include <vr/shaderUtils.h>
#include "Debug.h"
#include "DotVisitor.h"

Scene::Scene() : m_uniform_numberOfLights(-1)
{
  m_cameras.push_back(std::shared_ptr<Camera>(new Camera));
  m_selectedCamera = DEFAULT_CAMERA;
  m_root = std::shared_ptr<Group>(new Group);
  m_root->name = "Root ";
  m_shadowsEnabled = false;
  //Initalize visitors.
  m_renderer = std::shared_ptr<RenderVisitor>(new RenderVisitor());
  m_updater = std::shared_ptr<UpdateVisitor>(new UpdateVisitor());
  m_shadowMap = nullptr;
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
}

//TODO See if there is another way to init geometries other than initVisitor.
void Scene::add(std::shared_ptr<Group> node, int shader)
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

  //Add the new node to root graph.
  free(initVisitor);

  m_root->addChild(node);
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

const GroupVector& Scene::getGroups()
{
  return m_groups;
}

void Scene::render()
{

  //Render shadows
  if(m_shadowMap != nullptr)
  { 
    m_shadowMap->update();
    //Apply shadowmaps on all programs except the depthProgram.
    for(auto program : m_programs)
    {
      //Do not apply with the depthProgram itself.
      if(program != m_depthProgram)
      {
        m_shadowMap->apply(program, m_root);
      }
    }
  }

  applyCamera();

  m_updater->visit(*m_root);
  m_renderer->visit(*m_root);
  //std::cout << "Number of root children " << m_root->getChildren().size() << std::endl;
}
