#pragma once

#include <memory>
#include "Scene.h"
#include "FPSCounter.h"
#include "Camera.h"
#include "LodCallback.h"

class Application
{

public:

  Application(unsigned int width, unsigned int height);

  bool initResources(const std::string& model_filename, const std::string& vshader_filename, std::string& fshader_filename);
  void initView();

  void setScreenSize(unsigned int width, unsigned int height);

  std::shared_ptr<Camera> getCamera();

  void reloadScene();
  void render(GLFWwindow* window);
  void update(GLFWwindow* window);
  void processInput(GLFWwindow* window);

  bool loadLodObjects(std::vector<std::string> objectFiles);
  bool loadGroup(std::string model_filename, std::shared_ptr<Group> &group);
  void add(std::shared_ptr<Group> group);

private:

  //Default geometry if no argument is provided or failes to be loaded in.
  bool buildGeometry();

  //Load default terrain.
  bool loadTerrain();

  //Load a moving light with attached to a object.
  bool loadMovingLight();
  
  // Parent of all to be rendered
  std::shared_ptr<Scene> m_sceneRoot;

  std::shared_ptr<FPSCounter> m_fpsCounter;
  std::string m_loadedFilename, m_loadedVShader, m_loadedFShader;
  glm::uvec2 m_screenSize;
};