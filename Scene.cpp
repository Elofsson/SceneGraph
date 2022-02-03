#include "Scene.h"
#include <iostream>
#include <vr/shaderUtils.h>

Scene::Scene() : m_uniform_numberOfLights(-1)
{
  m_camera = std::shared_ptr<Camera>(new Camera);

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

  return true;
}

//TODO bruh, continue here and see how this should be handled with groups.
void Scene::add(std::shared_ptr<Light>& light)
{
  m_lights.push_back(light);
  std::shared_ptr<Group> group = std::shared_ptr<Group>(new Group());

  group->addChild(light->m_geometry);

  // Also add the mesh-node
  add(group);
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

//TODO See if there is another way to init geometries other than getGeometry method.
//FIXME Find a way to initialize geometry from a group.
void Scene::add(std::shared_ptr<Node> node)
{
  m_nodes.push_back(node);

  //for (auto geometry : group->getGeometry())
  //{
  //  geometry->initShaders(m_program);
  //  geometry->upload();
  //}
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
  //FIXME find a good way to calculate bounding box for nodes.
  BoundingBox box;
  //for (auto n : m_nodes)
    //box.expand(n->calculateBoundingBox());

  return box;
}

const GroupVector& Scene::getGroups()
{
  return m_groups;
}

void Scene::render()
{
  useProgram();

  // Update number of lights
  if (m_uniform_numberOfLights == -1) {
    const char *uniform_name = "numberOfLights";
    m_uniform_numberOfLights = glGetUniformLocation(m_program, uniform_name);
    if (m_uniform_numberOfLights == -1) {
      std::cerr << "Could not bind uniform " << uniform_name << std::endl;
    }
  }
  glUniform1i(m_uniform_numberOfLights, (GLint)m_lights.size());

  //FIXME fix a way to apply lights.
  // Apply lightsources
  //size_t i = 0;
  //for (auto l : m_lights)
  //{
    //l->apply(m_program, i++);
  //}

  //FIXME Replace with a renderVisitor
  //for (auto n : m_nodes)
    //n->render(m_program);
}
