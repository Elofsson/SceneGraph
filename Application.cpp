#include "Application.h"

#include <iostream>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vr/FileSystem.h>
#include <vr/shaderUtils.h>
#include <vr/DrawText.h>

#include "Scene.h"
#include "Loader.h"
#include "CircularMovementCallback.h"
#include "MovingLightCallback.h"
#include "RotateCallback.h"
#include <stdlib.h>
#include <time.h> 

Application::Application(unsigned int width, unsigned height) : m_screenSize(width, height)
{
  m_fpsCounter = std::make_shared<FPSCounter>();

}

bool Application::initResources(const std::string& model_filename, const std::string& vshader_filename, std::string& fshader_filename)
{
  std::cout << "Filename: " << model_filename << std::endl;
  
  m_loadedVShader = vshader_filename;
  m_loadedFShader = fshader_filename;
  m_loadedFilename = model_filename;

  m_sceneRoot = std::shared_ptr<Scene>(new Scene);

  if (!m_sceneRoot->initShaders(vshader_filename, fshader_filename))
    return false;

  //Create light.
  std::shared_ptr<Light> light2 = std::shared_ptr<Light>(new Light);
  light2->setDiffuse(glm::vec4(1, 1, 1, 1));
  light2->setSpecular(glm::vec4(1, 1, 1, 1));
  light2->setPosition(glm::vec4(1.0, 2.0, -2.0, 0.0));
  m_sceneRoot->add(light2);

  getCamera()->setScreenSize(m_screenSize);
  std::shared_ptr<Group> rootGroup = std::shared_ptr<Group>(new Group());

  if(!loadGroup(model_filename, rootGroup))
  {
    std::cerr << "Failed to load scene" << std::endl;

    //Build default
    if(!buildGeometry())
    {
      std::cerr << "Failed to load default" << std::endl;
      return false;
    }
  }

  else
  {
    m_sceneRoot->add(rootGroup);
    m_sceneRoot->createDotFile("dotfile");
  }
  return 1;
}

bool Application::loadMovingLight()
{
  //Load object to be attached to light.
  std::string lightObjectPath = "scenes/box.xml";
  std::shared_ptr<Group> lightObject = std::shared_ptr<Group>(new Group());
  if(!loadGroup(lightObjectPath, lightObject))
  {
    std::cerr << "Failed to load " << lightObjectPath << std::endl;
    return false;
  }

  //Light and object position.
  glm::vec3 position = glm::vec3(0, 1000, -250);

  //create light and add to root.
  std::shared_ptr<Light> movingLight = std::shared_ptr<Light>(new Light());
  movingLight->setAmbient(glm::vec4(0.0, 1.0, 0.5, 1.0));
  movingLight->setDiffuse(glm::vec4(0.2, 0.9, 0.9, 1.0));
  movingLight->setSpecular(glm::vec4(0.0, 0.1, 0.1, 1.0));
  movingLight->setPosition(glm::vec4(position, 1));
  m_sceneRoot->getRoot()->getState()->addLight(movingLight);

  //Add light and set state to transform.
  std::shared_ptr<Transform> lightTransform = std::shared_ptr<Transform>(new Transform(position.x, position.y, position.z));

  //Create callback.
  std::shared_ptr<MovingLightCallback> lightCallback = std::shared_ptr<MovingLightCallback>(new MovingLightCallback(lightTransform, movingLight));

  //Add callback and add to scene.
  lightTransform->addCallback(lightCallback);
  lightTransform->addChild(lightObject);
  m_sceneRoot->add(lightTransform);
  return true;
}

bool Application::buildGeometry()
{
  //Load default scene.
  std::string ironman_modelfile = "scenes/custom.xml";
  std::shared_ptr<Group> ironmanModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(ironman_modelfile, ironmanModel))
  {
    return false;
  }

  m_sceneRoot->add(ironmanModel);

  //Build level of detail objects.
  std::vector<std::string> cowLodModels;
  cowLodModels.push_back("models/cow_0.99.obj");
  cowLodModels.push_back("models/cow_0.5.obj");
  cowLodModels.push_back("models/cow_0.3.obj");
  cowLodModels.push_back("models/cow_0.1.obj");
  cowLodModels.push_back("models/cow_0.05.obj");
  cowLodModels.push_back("models/cow_0.01.obj");
  loadLodObjects(cowLodModels);
  loadTerrain();

  
  loadMovingLight();

  return true;
}

bool Application::loadLodObjects(std::vector<std::string> objectFiles)
{
  std::shared_ptr<Group> lodRoot = std::shared_ptr<Group>(new Group());
  lodRoot->name = "Lod root";
  for(auto modelFile : objectFiles)
  {
    std::shared_ptr<Group> lodGroup = std::shared_ptr<Group>(new Group());
    lodGroup->name = modelFile;
    if(!loadGroup(modelFile, lodGroup))
    {
      return false;
    }
    lodRoot->addChild(lodGroup);
  }
  
  //Set wireframe for the whole lod group.
  std::shared_ptr<State> lodState = std::shared_ptr<State>(new State());
  lodState->setPolygonMode(GL_LINE);
  lodRoot->setState(lodState);

  //Add LOD callback.
  std::shared_ptr<LodCallback> lodCallback = std::shared_ptr<LodCallback>(new LodCallback(lodRoot, m_sceneRoot->getCamera()));
  m_sceneRoot->getRoot()->addCallback(lodCallback);
  
  //Set scale.
  std::shared_ptr<Transform> lodTransform = std::shared_ptr<Transform>(new Transform(0, 0, 0));
  lodTransform->translate(glm::vec3(-200, -50, 200));
  lodTransform->scale(glm::vec3(0.1, 0.1, 0.1));
  lodTransform->addChild(lodRoot);
  m_sceneRoot->add(lodTransform);
  return true;
}

bool Application::loadTerrain()
{
  std::srand(time(NULL));
  std::shared_ptr<Group> terrainRoot = std::shared_ptr<Group>(new Group());
  terrainRoot->name = "Terrain root";

  //Load trees.
  std::string treeFile = "models/lowpolytree.obj";
  std::shared_ptr<Group> treeModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(treeFile, treeModel))
  {
    std::cerr << "Failed to load " << treeFile << std::endl; 
    return false;
  }


  //Radius used for random generation translations. 
  BoundingBox sceneBox = m_sceneRoot->calculateBoundingBox();
  int radius = sceneBox.getRadius() / 2;

  for(unsigned int i = 0; i < 25; i++)
  {
    std::shared_ptr<Transform> treeTransform = std::shared_ptr<Transform>(new Transform(0, 0, 0));
    treeTransform->addChild(treeModel);

    float x = std::rand() % radius;
    float z = std::rand() % radius;
    treeTransform->translate(glm::vec3(x, -22, z));
    treeTransform->scale(glm::vec3(15, 15, 15));
    terrainRoot->addChild(treeTransform);
  }

  //Load montains
  std::string mountainFile = "scenes/mountain.xml";
  std::shared_ptr<Group> mountainModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(mountainFile, mountainModel))
  {
    std::cerr << "Failed to load " << mountainFile << std::endl;
    return false;
  }

  for(unsigned int i = 0; i < 25; i++)
  {
    std::shared_ptr<Transform> mountainTransform = std::shared_ptr<Transform>(new Transform());
    mountainTransform->addChild(mountainModel);

    //Randomize x and y values whith whole scene bounding box radius.
    float x = 0;
    float z = 0;
    x -= std::rand() % radius;
    z -= std::rand() % radius;
    mountainTransform->translate(glm::vec3(x, -22, z));

    //set random scale with a cap of 20 and lowercap 3.
    int higherCap = 20;
    int lowerCap = 3;
    float scaleX = std::rand() % higherCap + lowerCap;
    float scaleY = std::rand() % higherCap + lowerCap;
    float scaleZ = std::rand() % higherCap + lowerCap;
    mountainTransform->scale(glm::vec3(scaleX, scaleY, scaleZ));

    //Randomize rotations.
    float rotation = std::rand() % 180;
    mountainTransform->rotate(glm::vec3(0, 1, 0), rotation);

    //Add to terrain root.
    terrainRoot->addChild(mountainTransform);
  }

  m_sceneRoot->add(terrainRoot);
  return true;
}

bool Application::loadGroup(std::string model_filename, std::shared_ptr<Group> &group)
{
  std::string ext = vr::FileSystem::getFileExtension(model_filename);
  if (ext == "xml" || ext == "XML"){
    if (!loadSceneFile(model_filename, group))
    {
      return false;
    }

    if (group->empty())
    {
      std::cerr << "Empty scene, something when wrong when loading files" << std::endl;
      return false;
    }
  }

  else
  {
    group = load3DModelFile(model_filename);
    if(!group)
    {
      return false;
    }
  }

  return true;
}

void Application::reloadScene()
{
  initResources(m_loadedFilename, m_loadedVShader, m_loadedFShader);
  initView();
}

void Application::initView()
{
  // Compute a bounding box around the whole scene
  BoundingBox box = m_sceneRoot->calculateBoundingBox();
  float radius = box.getRadius();
  std::cout << "Radius: " << radius << std::endl;

  // Compute the diagonal and a suitable distance so we can see the whole thing
  float distance = radius * 1.5f;
  glm::vec3 eye = glm::vec3(0, radius, distance);

  glm::vec3 direction = glm::normalize(box.getCenter() - eye);

  std::shared_ptr<Light> light = m_sceneRoot->getLights().front();
  glm::vec4 position;
  position = glm::vec4(eye + glm::vec3(3, 2, 0), 1);
  light->setPosition(position);

  m_sceneRoot->resetTransform();

  // Set the position/direction of the camera
  getCamera()->set(eye, direction, glm::vec3(0.0, 1.0, 0.0));
  getCamera()->setNearFar(glm::vec2(0.1, distance * 20));

  getCamera()->setSceneScale(0.01f * radius);

  getCamera()->setFov(90);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
}

void Application::render(GLFWwindow* window)
{
  glClearColor(0.45f, 0.45f, 0.45f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_fpsCounter->render(window);

  m_sceneRoot->render();
}

void Application::update(GLFWwindow* window)
{
  m_sceneRoot->useProgram();
  m_sceneRoot->applyCamera();

  render(window);
}


void Application::processInput(GLFWwindow* window)
{
  getCamera()->processInput(window);
}

void Application::setScreenSize(unsigned int width, unsigned int height)
{
  getCamera()->setScreenSize(glm::uvec2(width, height));
  glViewport(0, 0, width, height);
}


std::shared_ptr<Camera> Application::getCamera()
{
  return m_sceneRoot->getCamera();
}

void Application::add(std::shared_ptr<Group> group)
{
  if(m_sceneRoot != nullptr)
  {
    m_sceneRoot->add(group);
  }

  else
  {
    std::cerr << " Failed to add geometry" << std::endl;
  }
}
