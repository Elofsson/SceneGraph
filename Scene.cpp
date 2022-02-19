#include "Scene.h"
#include <iostream>
#include <vr/shaderUtils.h>
#include "Debug.h"
#include "DotVisitor.h"

Scene::Scene() : m_uniform_numberOfLights(-1)
{
  m_camera = std::shared_ptr<Camera>(new Camera);
  m_root = std::shared_ptr<Group>(new Group);
  m_root->name = "Root ";
}

bool Scene::initShaders(const std::string& vshader_filename, const std::string& fshader_filename)
{
  /* Compile and link shaders */
  int id = addShader(vshader_filename, fshader_filename);
  if(id == -1)
    return false;

  m_camera->init(m_programs[id]);

  //Set root state.
  std::shared_ptr<State> rootState = std::shared_ptr<State>(new State());
  rootState->setProgram(m_programs[id]);
  rootState->setPolygonMode(GL_FILL);
  rootState->setCullFace(true);
  m_root->setState(rootState);

  //Initalize visitors.
  m_renderer = std::shared_ptr<RenderVisitor>(new RenderVisitor());
  m_updater = std::shared_ptr<UpdateVisitor>(new UpdateVisitor());

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

//Currently apply lights to all children.
void Scene::add(std::shared_ptr<Light>& light)
{
  //std::shared_ptr<Group> group = std::shared_ptr<Group>(new Group());
  //group->addChild(light->m_geometry);
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
  return m_root->getState()->getLights();
}

std::vector<GLuint> Scene::getPrograms() const
{
  return m_programs;
}

std::shared_ptr<Camera> Scene::getCamera()
{
  return
    m_camera;
}

Scene::~Scene()
{
  for(auto program : m_programs)
  {
    glDeleteProgram(program);
  }
}

void Scene::applyCamera()
{
  for(auto program: m_programs)
  {
    m_camera->apply(program);
  }
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
  //Initalize new node with initVisitor.
  if(m_programs.size() > shader &&!(shader < 0))
  {
    GLuint program = m_programs[shader];
    InitVisitor *initVisitor = new InitVisitor(program);
    initVisitor->visit(*node);

    //Add the new node to root graph.
    m_root->addChild(node);
  }
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
  m_updater->visit(*m_root);
  m_renderer->visit(*m_root);
  //std::cout << "Number of root children " << m_root->getChildren().size() << std::endl;
}
