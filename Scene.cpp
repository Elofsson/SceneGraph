#include "Scene.h"
#include <iostream>
#include <vr/shaderUtils.h>

#include "CircularMovementCallback.h"

Scene::Scene() : m_uniform_numberOfLights(-1)
{
  m_camera = std::shared_ptr<Camera>(new Camera);
  m_root = std::shared_ptr<Group>(new Group);
  m_program = glCreateProgram();
}

bool Scene::initShaders(const std::string& vshader_filename, const std::string& fshader_filename)
{
  /* Compile and link shaders */
  GLint link_ok = GL_FALSE;
  GLint validate_ok = GL_FALSE;
  GLuint vs, fs;
  if ((vs = vr::loadShader(vshader_filename, GL_VERTEX_SHADER)) == 0) return false;
  if ((fs = vr::loadShader(fshader_filename, GL_FRAGMENT_SHADER)) == 0) return false;

  glAttachShader(m_program, vs);
  glAttachShader(m_program, fs);
  glLinkProgram(m_program);
  glGetProgramiv(m_program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    vr::printCompilationError(m_program);
    return false;
  }
  glValidateProgram(m_program);
  glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validate_ok);
  if (!validate_ok) {
    fprintf(stderr, "glValidateProgram:");
    vr::printCompilationError(m_program);
    return false;
  }

  m_camera->init(m_program);
  m_root->getState()->setProgram(m_program);
  m_root->getState()->setPolygonMode(GL_FILL);
  m_root->getState()->setCullFace(true);

  return true;
}

//Currently apply lights to all children.
void Scene::add(std::shared_ptr<Light>& light)
{
  //std::shared_ptr<Group> group = std::shared_ptr<Group>(new Group());
  //group->addChild(light->m_geometry);
  m_lights.push_back(light);
  m_root->getState()->addLight(light);

  // Also add the mesh-node
  //add(group);
}

const std::shared_ptr<Group> Scene::getRoot()
{
  return m_root;
}

const LightVector& Scene::getLights()
{
  return
    m_lights;
}

GLuint Scene::getProgram() const
{
  return
    m_program;
}

std::shared_ptr<Camera> Scene::getCamera()
{
  return
    m_camera;
}

Scene::~Scene()
{
  glDeleteProgram(m_program);
}

void Scene::applyCamera()
{
  m_camera->apply(m_program);
}

void Scene::useProgram()
{
  glUseProgram(m_program);
}

//TODO See if there is another way to init geometries other than initVisitor.
void Scene::add(std::shared_ptr<Group> node)
{

  //node->getState()->setPolygonMode(GL_LINE);

  //Initalize new node with initVisitor.
  InitVisitor *initVisitor = new InitVisitor(m_program);
  initVisitor->visit(*node);

  //Add the new node to root graph.
  m_root->addChild(node);
}

void Scene::resetTransform()
{
  //FIXME move reset of transforms to transform.
  //for (auto n : m_nodes)
    //n->resetTransform();
}

const NodeVector& Scene::getNodes()
{
  return m_nodes;
}


std::shared_ptr<Node> Scene::getNode(size_t i)
{
  return m_nodes[i];
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
  useProgram();

  UpdateVisitor *updater = new UpdateVisitor(m_program);
  updater->visit(*m_root);

  RenderVisitor *render = new RenderVisitor(m_program);
  render->visit(*m_root);
}
