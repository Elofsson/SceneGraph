#pragma once

#include <memory>
#include "Scene.h"
#include "FPSCounter.h"
#include "Camera.h"
#include "LodCallback.h"

class Application
{

public:

  /**
   * @brief Construct a new Application object
   * 
   * @param width Width of the application
   * @param height Height of the application.
   */
  Application(unsigned int width, unsigned int height);

  /**
   * @brief Initalize the application with shaders and a default model either as a
   *        obj file or stored in a xml format. If the file is could  not be loaded
   *        a default scene will be loaded instead
   * 
   * @param model_filename Path to model to be loaded
   * @param vshader_filename Path to vertex shader.
   * @param fshader_filename Path to fragment shader.
   * @return true 
   * @return false 
   */
  bool initResources(const std::string& model_filename, const std::string& vshader_filename, std::string& fshader_filename);
  
  /**
   * @brief Initalize the view.
   * 
   */
  void initView();

  /**
   * @brief Set the Screen Size.
   * 
   * @param width Width of the screen.
   * @param height Height of the screen.
   */
  void setScreenSize(unsigned int width, unsigned int height);


  /**
   * @brief Get the Camera object
   * 
   * @return std::shared_ptr<Camera> 
   */
  std::shared_ptr<Camera> getCamera();


  /**
   * @brief Reload the scene and all contents.
   * 
   */
  void reloadScene();

  /**
   * @brief Render the application.
   * 
   * @param window GLFWwindow.
   */
  void render(GLFWwindow* window);

  /**
   * @brief Update the application.
   * 
   * @param window GLFW window.
   */
  void update(GLFWwindow* window);

  /**
   * @brief Key input.
   * 
   * @param window GLFW window.
   */
  void processInput(GLFWwindow* window);

  /**
   * @brief Load level of detail objects. The
   *        list should be sorted in best detailed to 
   *        the worst detailed.
   * 
   * @param objectFiles Array of filePaths to be used as level of detail objects.
   * @return true succesfully loaded
   * @return false failed to load
   */
  bool loadLodObjects(std::vector<std::string> objectFiles);
  
  /**
   * @brief Load a new group.
   * 
   * @param model_filename File path to model, xml or obj.
   * @param group Group where contents from file will be placed to.
   * @return true when successfully read
   * @return false failed to read file.
   */
  bool loadGroup(std::string model_filename, std::shared_ptr<Group> &group);

  /**
   * @brief Add a new group to the application.
   * 
   * @param group New group.
   */
  void add(std::shared_ptr<Group> group);

  void switchCamera();

  int addCamera(std::shared_ptr<Camera> camera, bool selectCamera = false);

private:

  //Default geometry if no argument is provided or failes to be loaded in.
  bool buildGeometry();

  //Load default terrain.
  bool loadTrees(int radius);

  bool loadMountains(int radius);

  //Load a moving light with attached to a object.
  bool loadMovingLight();

  bool loadFurry();

  bool loadSkybox(std::vector<std::string> textures, const std::string& model_filename, const std::string& vshader_filename, std::string& fshader_filename);
  
  // Parent of all to be rendered
  std::shared_ptr<Scene> m_sceneRoot;

  std::shared_ptr<FPSCounter> m_fpsCounter;
  std::string m_loadedFilename, m_loadedVShader, m_loadedFShader;
  std::vector<int> m_cameras;
  std::vector<int> m_programs;
  glm::uvec2 m_screenSize;
};