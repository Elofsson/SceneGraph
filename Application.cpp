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
#include "MovingTransformCallback.h"
#include "RotateCallback.h"
#include <stdlib.h>
#include <time.h> 
#include "ControllableObjectCallback.h"


Application::Application(unsigned int width, unsigned height) : m_screenSize(width, height)
{
  std::cout << "Application init " << std::endl;
  m_fpsCounter = std::make_shared<FPSCounter>();
  m_lastFrameTime = 0.0f;
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
  
  //Init shadows.
  std::string vshadowShader = "shaders/shadowmap-shading.vert.glsl";
  std::string fshadowShader = "shaders/shadowmap-shading.frag.glsl";
  if(!m_sceneRoot->initShadows(vshadowShader, fshadowShader))
    return false;
  

  //Skybox shaders.
  std::string vskyboxShader = "shaders/skybox-shading.vert.glsl";
  std::string fskyboxShader = "shaders/skybox-shading.frag.glsl";
  
  //Skybox textures.
  std::vector<std::string> skyboxTextures;
  skyboxTextures.push_back("models/skybox/right.jpg");
  skyboxTextures.push_back("models/skybox/left.jpg");
  skyboxTextures.push_back("models/skybox/top.jpg");
  skyboxTextures.push_back("models/skybox/bottom.jpg");
  skyboxTextures.push_back("models/skybox/front.jpg");
  skyboxTextures.push_back("models/skybox/back.jpg");

  //Skybox model.
  std::string skyboxModelFile = "models/box.obj";
  if(!loadSkybox(skyboxTextures, skyboxModelFile, vskyboxShader, fskyboxShader))
  {
    std::cout << "Failed to load skybox " << std::endl;
    return false;
  }

  //Load debug object for GBuffer.
  std::string gbufferDebugObjFile = "models/plane.obj";
  std::shared_ptr<Group> gbufferDebugObj = std::shared_ptr<Group>(new Group);
  if(!loadGroup(gbufferDebugObjFile, gbufferDebugObj, true))
  {
    std::cout << "Failed to load GBuffer debug object " << gbufferDebugObjFile << std::endl;
    return false; 
  }

  //initalize the GBuffer.
  if(!m_sceneRoot->initGBuffer(gbufferDebugObj))
  {
    std::cout << "Failed to load GBuffer " << std::endl;
    return false;
  }

  //Add camera.
  m_cameras.push_back(m_sceneRoot->getSelectedCameraId());

  if(!initPlayer())
  {
    std::cout << "Failed to load player" << std::endl;
    //return false;
  }

  //Create light.
  std::shared_ptr<Light> light2 = std::shared_ptr<Light>(new Light);
  light2->setDiffuse(glm::vec4(1, 1, 1, 1));
  light2->setSpecular(glm::vec4(1, 1, 1, 1));
  light2->setPosition(glm::vec4(1.0, 2.0, -2.0, 1.0));
  m_sceneRoot->add(light2);

  getCamera()->setScreenSize(m_screenSize);
  std::shared_ptr<Group> rootGroup = std::shared_ptr<Group>(new Group());

  if(!loadGroup(model_filename, rootGroup, true))
  {
    std::cerr << "Failed to load scene" << std::endl;

    //Build default
    if(!buildGeometry())
    {
      std::cerr << "Failed to load default" << std::endl;
      return false;
    }

    m_sceneRoot->createDotFile("dotfile");
  }

  else
  {
    m_sceneRoot->add(rootGroup);
    m_sceneRoot->createDotFile("dotfile");
  }

  return 1;
}

bool Application::loadSkybox(std::vector<std::string> textures, const std::string& modelfilename, const std::string& vshaderfilename, std::string& fshaderfilename)
{
  //Init skybox.
  int shaderId = m_sceneRoot->addShader(vshaderfilename, fshaderfilename);
  if(shaderId == -1)
  {
    std::cout << "Failed to load skybox shader " << std::endl;
    return false;
  }

  m_sceneRoot->setSkybox(shaderId, textures, modelfilename);
  
  return true;
}

bool Application::loadMovingObject(std::string objectPath)
{
  //Load object to be attached to light.
  std::shared_ptr<Group> object = std::shared_ptr<Group>(new Group());
  if(!loadGroup(objectPath, object, true))
  {
    std::cout << "----------------------------Failed to load " << objectPath  << std::endl;
    return false;
  }

  //Light and object position.
  glm::vec3 origin = glm::vec3(0, 200, 0);

  //Add light and set state to transform.
  std::shared_ptr<Transform> transform = std::shared_ptr<Transform>(new Transform());

  //Create callback.
  float radius = 100.0f;
  std::shared_ptr<MovingTransformCallback> callback = std::shared_ptr<MovingTransformCallback>(new MovingTransformCallback(transform, origin, radius));

  //Add callback and add to scene.
  object->addCallback(callback);
  transform->addChild(object);
  m_sceneRoot->add(transform);

  return true;
}

bool Application::buildGeometry()
{

  //Build level of detail objects.
  std::vector<std::string> cowLodModels;
  cowLodModels.push_back("models/cow_0.99.obj");
  cowLodModels.push_back("models/cow_0.5.obj");
  cowLodModels.push_back("models/cow_0.3.obj");
  cowLodModels.push_back("models/cow_0.1.obj");
  cowLodModels.push_back("models/cow_0.05.obj");
  cowLodModels.push_back("models/cow_0.01.obj");

  //loadLodObjects(cowLodModels);
  std::string ironman_modelfile = "scenes/box.xml";
  std::shared_ptr<Group> ironmanModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(ironman_modelfile, ironmanModel, true))
  {
    return false;
  }

  //Create rootgroup with physics property.
  std::shared_ptr<Group> rootGroup = std::shared_ptr<Group>(new Group);

  float offset = 1;
  for(int i = 1; i  < 10; i++)
  {
    std::shared_ptr<Transform> transform = std::shared_ptr<Transform>(new Transform);
    transform->translate(glm::vec3(0, i * offset, 0));
    transform->addChild(ironmanModel);

    //Set physics
    std::shared_ptr<PhysicsState> physics = std::shared_ptr<PhysicsState>(new PhysicsState);
    physics->setType(reactphysics3d::BodyType::DYNAMIC);
    physics->setMass(1);
    physics->setBounciness(0.5);
    physics->setFriction(0.1);
    physics->setShape(SHAPE_BOX);
    transform->setPhysics(physics);
    std::string name = "ball_";
    name.append(std::to_string(i));
    transform->name = name;
    rootGroup->addChild(transform);
  }


  //m_sceneRoot->add(ironmanModel);

  rootGroup->name = "Root group for balls";

  m_sceneRoot->add(rootGroup);

  if(!loadTerrain())
    return false;

  //Create the terrain within a certain radius.
  BoundingBox sceneBox = m_sceneRoot->calculateBoundingBox();
  int radius = sceneBox.getRadius() / 4;
  if(!loadTrees(radius))
    return false;
  
  //if(!loadMountains(radius))
    //return false;

  //if(!loadFurry())
    //return false;

  //std::string objectPath = "scenes/sphere.xml";
  //if(!loadMovingObject(objectPath))
    //return false;

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
    if(!loadGroup(modelFile, lodGroup, true))
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


//Has to be called after a camera has been created.
bool Application::initPlayer()
{
  //Load player model.
  std::string playerModelFile = "scenes/sphere.xml";
  std::shared_ptr<Group> playerModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(playerModelFile, playerModel, true))
  {
    std::cout << "Failed to load player model " << playerModelFile << std::endl;
    return false;
  }

  //Load projectile model
  std::string projectileModelFile = "scenes/projectile.xml";
  std::shared_ptr<Group> projectileModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(projectileModelFile, projectileModel, true))
  {
    std::cout << "Failed to load projectile model " << projectileModelFile << std::endl;
    return false;
  }
  
  //TODO this is due to a problem with the first transform in a subtree being ignored and interpreted as a group, this should be fixed.
  //Create rootgroup with physics property.
  std::shared_ptr<Group> rootGroup = std::shared_ptr<Group>(new Group);


  //Init player with movementspeed and camera.
  float speed = 750.0;
  m_player = std::shared_ptr<Player>(new Player(speed, m_sceneRoot->getSelectedCamera()));

  //Set player model with physics.
  std::shared_ptr<PhysicsState> playerPhysics = std::shared_ptr<PhysicsState>(new PhysicsState);
  playerPhysics->setType(reactphysics3d::BodyType::DYNAMIC);
  playerPhysics->setMass(10);
  playerPhysics->setBounciness(0.05);
  playerPhysics->setFriction(1.0);
  playerPhysics->setShape(SHAPE_SPHERE);
  std::shared_ptr<Transform> playerTransform = std::shared_ptr<Transform>(new Transform);
  playerTransform->translate(glm::vec3(1, 1, 1));
  playerTransform->addChild(playerModel);
  m_player->setModel(playerTransform, playerPhysics);

  //Set the weapon projectile model.
  m_player->setWeapon(projectileModel);

  //Add playermodel to scene.
  rootGroup->addChild(playerTransform);
  m_sceneRoot->add(rootGroup);

  //Set player view as default.
  m_playerViewEnabled = true;
  return true;
}

bool Application::loadTrees(int radius)
{
  //Load trees.
  std::string treeFile = "models/lowpolytree.obj";
  std::shared_ptr<Group> treeModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(treeFile, treeModel, true))
  {
    std::cerr << "Failed to load " << treeFile << std::endl; 
    return false;
  }

  std::srand(time(NULL));

  //Radius used for random generation translations. 
  std::shared_ptr<Group> treeRoot = std::shared_ptr<Group>(new Group());
  for(unsigned int i = 0; i < 25; i++)
  {
    std::shared_ptr<Transform> treeTransform = std::shared_ptr<Transform>(new Transform(0, 0, 0));
    treeTransform->addChild(treeModel);

    //Create physics
    std::shared_ptr<PhysicsState> physics = std::shared_ptr<PhysicsState>(new PhysicsState);
    physics->setType(reactphysics3d::BodyType::STATIC);
    physics->setMass(5);
    physics->setBounciness(0.5);
    physics->setFriction(0.1);
    physics->setShape(SHAPE_BOX);
    treeTransform->setPhysics(physics);

    //Set name.
    std::string name = "tree_";
    name.append(std::to_string(i));
    treeTransform->name = name;

    //Determine the sign of x and y coordinates.
    int signX = std::rand() % 2;
    int signZ = std::rand() % 2;
    float x = 1;
    float z = 1;
    if(signX == 1)
    {
      x = -1;
    }

    if(signZ == 1)
    {
      z = -1;
    }

    //Translate, scale and add to scene.
    x *= std::rand() % radius;
    z *= std::rand() % radius;
    treeTransform->translate(glm::vec3(x, 1.2, z));
    treeTransform->scale(glm::vec3(0.4, 0.4, 0.4));
    treeRoot->addChild(treeTransform);
  }

  m_sceneRoot->add(treeRoot);
  return true;
}

bool Application::loadMountains(int radius)
{
  //Load model.
  std::string mountainFile = "scenes/mountain.xml";
  std::shared_ptr<Group> mountainModel = std::shared_ptr<Group>(new Group());
  if(!loadGroup(mountainFile, mountainModel, true))
  {
    std::cerr << "Failed to load " << mountainFile << std::endl;
    return false;
  }

  std::srand(time(NULL));

  //Create 25 transforms containing mountain model.
  std::shared_ptr<Group> montainRoot = std::shared_ptr<Group>(new Group());
  for(unsigned int i = 0; i < 1; i++)
  {
    std::shared_ptr<Transform> mountainTransform = std::shared_ptr<Transform>(new Transform());
    mountainTransform->addChild(mountainModel);

    //Randomize x and y values whith whole scene bounding box radius.
    float x = 0;
    float z = 0;
    x -= std::rand() % 3;
    z -= std::rand() % 3;
    mountainTransform->translate(glm::vec3(x, 0.1, z));

    //set random scale with a cap of 20 and lowercap 3.
    int higherCap = 5;
    int lowerCap = 1;
    float scaleX = std::rand() % higherCap + lowerCap;
    float scaleY = std::rand() % higherCap + lowerCap;
    float scaleZ = std::rand() % higherCap + lowerCap;
    mountainTransform->scale(glm::vec3(scaleX, scaleY, scaleZ));

    //Randomize rotations.
    //float rotation = std::rand() % 180;
    //mountainTransform->rotate(glm::vec3(0, 1, 0), rotation);


    //Create physics
    std::shared_ptr<PhysicsState> physics = std::shared_ptr<PhysicsState>(new PhysicsState);
    physics->setType(reactphysics3d::BodyType::DYNAMIC);
    physics->setMass(1);
    physics->setBounciness(0.5);
    physics->setFriction(0.1);
    physics->setShape(SHAPE_BOX);
    mountainTransform->setPhysics(physics);

    //Add to terrain root.
    montainRoot->addChild(mountainTransform);
  }

  //Add montains to scene.
  m_sceneRoot->add(montainRoot);
  return true;
}

bool Application::loadTerrain()
{
  //Load terrain model.
  std::string terrainModel = "scenes/terrain.xml";
  std::shared_ptr<Group> terrain = std::shared_ptr<Group>(new Group);
  if(!loadGroup(terrainModel, terrain, true))
  {
    std::cout << "Failed to load model: " << terrainModel << std::endl;
    return false;
  }

  m_sceneRoot->add(terrain, true);
  return true;
}

bool Application::loadGroup(std::string model_filename, std::shared_ptr<Group> &group, bool enablePhysics)
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

bool Application::loadFurry()
{ 

  //Load fur shaders.
  std::string vshader = "shaders/fur-shading.vert.glsl";
  std::string fshader = "shaders/fur-shading.frag.glsl";
  int shaderId = m_sceneRoot->addShader(vshader, fshader);
  if(shaderId < 0)
  {
    std::cout << "Failed to load shaders : " << vshader << " AND " << fshader << std::endl;
    return false;
  }

  //Load object.
  std::string modelName = "models/Mike.obj";
  std::shared_ptr<Group> furryGroup = std::shared_ptr<Group>(new Group);
  if(!loadGroup(modelName, furryGroup, false))
  {
    std::cout << "Failed to load furry object " << modelName << std::endl;
    return false;
  }

  //Create fur state.
  int furLayer = 20;
  float furLength = 0.001;
  float furOffset = 0.001;
  std::shared_ptr<FurState> furState = std::shared_ptr<FurState>(new FurState(furLayer, furLength, furOffset));
  furState->init("textures/furPattern.png", 1920, 1920);
  
  //Add furstate to state.
  std::shared_ptr<State> state = std::shared_ptr<State>(new State);
  state->setFurShading(furState);
  std::cout << "FUR STATE program: " << m_sceneRoot->getProgram(shaderId) << std::endl;
  state->setProgram(m_sceneRoot->getProgram(shaderId));
  furryGroup->setState(state);

  //Create transform to scale the object.
  std::shared_ptr<Transform> transform = std::shared_ptr<Transform>(new Transform);
  transform->scale(glm::vec3(25, 25, 25));
  transform->addChild(furryGroup);

  //Add to scene.
  m_sceneRoot->add(transform, false, shaderId);
  //addPhysics(transform);

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
  position = glm::vec4(eye + glm::vec3(3, 2, 0), 0.0);
  light->setPosition(position);

  // Set the position/direction of the camera
  getCamera()->set(glm::vec3(0.0, 0.5, 0.0), direction, glm::vec3(0.0, 1.0, 0.0));
  getCamera()->setNearFar(glm::vec2(0.1, distance * 20));
  getCamera()->setSceneScale(0.01f * radius);
  getCamera()->setFov(90);

  //Create a second camera and with the same position as the lightning..
  std::shared_ptr<Camera> secondCamera = std::shared_ptr<Camera>(new Camera);
  secondCamera->set(position, direction, glm::vec3(0.0, 1.0, 0.0));
  secondCamera->setNearFar(glm::vec2(0.1, distance * 20));
  secondCamera->setSceneScale(0.1f * radius);
  secondCamera->setFov(90);
  secondCamera->setScreenSize(m_screenSize);
  addCamera(secondCamera);

  //Add a shadowMap for this light with the specified camera.
  m_sceneRoot->addShadowMap(light, secondCamera);

  //Load object that should be next to the light and the second camera.
  /*std::shared_ptr<Group> lightGroup = std::shared_ptr<Group>(new Group);
  std::string lightModel = "scenes/sphere.xml";
  if(!loadGroup(lightModel, lightGroup, true))
  {
    std::cout << "Failed to load model for the light: " << lightModel << std::endl;
    return;
  }

  //Create a transform to move the object to the light and cameras position. 
  std::shared_ptr<Transform> lightModelPos = std::shared_ptr<Transform>(new Transform());
  lightModelPos->addChild(lightGroup);
  lightModelPos->scale(glm::vec3(2, 2, 2));

  //Create callback which moves the object, light and camera together and add to state
  std::shared_ptr<ControllableObjectCallback> movableLightCallback 
                    = std::shared_ptr<ControllableObjectCallback>(new ControllableObjectCallback(secondCamera, lightModelPos));
  std::shared_ptr<State> groupState = std::shared_ptr<State>(new State);
  groupState->addLight(light);
  lightGroup->setState(groupState);
  lightModelPos->addCallback(movableLightCallback);

  //Finally add the object to the scene.
  m_sceneRoot->add(lightModelPos);*/

  //Set some scene settings.
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
}

int Application::addCamera(std::shared_ptr<Camera> camera, bool selectCamera)
{
  int cameraId = m_sceneRoot->addCamera(camera);
  m_cameras.push_back(cameraId);

  if(selectCamera)
    m_sceneRoot->selectCamera(cameraId);
    
  return cameraId;
}

void Application::render(GLFWwindow* window)
{
  glClearColor(0.45f, 0.45f, 0.45f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  m_sceneRoot->render();
  m_sceneRoot->debugGBuffer(m_screenSize[0], m_screenSize[1]);
  m_fpsCounter->render(window);
  drawControls();
}

void Application::update(GLFWwindow* window)
{
  //Increase timestep.
  float time = glfwGetTime();
  m_timeStep = time - m_lastFrameTime;
  m_lastFrameTime = time;

  m_sceneRoot->update(m_timeStep);
  render(window);
}


void Application::processInput(GLFWwindow* window)
{
  if(m_playerViewEnabled)
  {
    std::shared_ptr<Group> playerOutputs = m_player->processInput(window, m_timeStep);
    if(playerOutputs != nullptr)
    {
      m_sceneRoot->add(playerOutputs);
    }
  }
  
  else
  {
    getCamera()->processInput(window, m_timeStep);
  }
}

void Application::setScreenSize(unsigned int width, unsigned int height)
{
  for(auto cameraId : m_cameras)
  {
    std::shared_ptr<Camera> camera = m_sceneRoot->getCamera(cameraId);
    if(camera != nullptr)
    {
      camera->setScreenSize(glm::uvec2(width, height));
    }
  }
  glViewport(0, 0, width, height);
}

std::shared_ptr<Camera> Application::getCamera()
{
  return m_sceneRoot->getSelectedCamera();
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

void Application::toggleShadows()
{
  m_sceneRoot->enableShadows(!m_sceneRoot->shadowsIsEnabled());
}

void Application::togglePhysicsDebug()
{
  auto physics = m_sceneRoot->getPhysicsWorld();
  physics->setDebugMode(!physics->debugEnabled());
}

void Application::toggleWireFrame()
{
  auto state = m_sceneRoot->getRoot()->getState();
  if(state->getPolygonMode() == GL_LINE)
  {
    state->setPolygonMode(GL_FILL);
  }

  else
  {
    state->setPolygonMode(GL_LINE);
  }
}

void Application::togglePlayer()
{
  if(m_playerViewEnabled)
  {
    m_playerViewEnabled = false;
  }
  else
  {
    m_playerViewEnabled = true;
  }
}


//TODO fix this method, works but is very bad implemented.
void Application::switchCamera()
{
  int currentCameraId = m_sceneRoot->getSelectedCameraId();
  std::cout << "Current camera: " << currentCameraId << std::endl;
  for(unsigned int i = 0; i < m_cameras.size(); i++)
  {
    int cameraId = m_cameras[i];
    if(currentCameraId == cameraId)
    {
      std::cout << "FOund camera" << std::endl;

      //Determine if the next element should be used or if the
      //The if the first camera is to be selected again.
      i++;
      int cameraIndex = 0;
      if(i < m_cameras.size())
      {
        std::cout << "Use next camera" << std::endl;
        cameraIndex = i;
      }

      //If the this was the last camera, select the first one again,
      else
      {
        std::cout << "Start from beginning" << std::endl;
        cameraIndex = 0;
      }
      
      std::cout << "Use camera at index: " << cameraIndex << std::endl;
      m_sceneRoot->selectCamera(m_cameras[cameraIndex]);
      return;
    }
  }
}

void Application::drawControls()
{
  vr::Text::setColor(glm::vec4(0, 1, 0, 0.8));
  vr::Text::setFontSize(20);

  std::string str = "Change Camera: C"; 
  vr::Text::drawText(m_screenSize[0], m_screenSize[1], 10, 50, str.c_str());

  str = "Toggle shadows: V";
  vr::Text::drawText(m_screenSize[0], m_screenSize[1], 10, 70, str.c_str());

  str = "Toggle debug of collision boxes: B";
  vr::Text::drawText(m_screenSize[0], m_screenSize[1], 10, 90, str.c_str());

  str = "Toggle wireframe: N";
  vr::Text::drawText(m_screenSize[0], m_screenSize[1], 10, 110, str.c_str());

  str = "Toggle player view: P";
  vr::Text::drawText(m_screenSize[0], m_screenSize[1], 10, 130, str.c_str());
  str = "(Note that change of camera, C, can not be used while in player view)";
  vr::Text::drawText(m_screenSize[0], m_screenSize[1], 10, 150, str.c_str());


  if(m_playerViewEnabled)
  {
    str = "Player view";
    vr::Text::drawText(m_screenSize[0], m_screenSize[1], m_screenSize[0] - 150, 30, str.c_str());
  }

  else
  {
    str = "Camera " + std::to_string(m_sceneRoot->getSelectedCameraId()); 
    vr::Text::drawText(m_screenSize[0], m_screenSize[1], m_screenSize[0] - 150, 30, str.c_str());
  }
  
}
