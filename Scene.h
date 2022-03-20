
#pragma once

#include <sstream>
#include "Geometry.h"
#include "Light.h"
#include "Camera.h"
#include "UpdateVisitor.h"
#include "RenderToTexture.h"
#include "ShadowMap.h"
#include "InitPhysicsVisitor.h"
#include "Physics.h"

class SkyBox;
class Scene;

#define DEFAULT_SHADER 0
#define DEFAULT_CAMERA 0

/// <summary>
/// Class that holds all mesh objects, lights and a camera
/// </summary>
class Scene
{
public:

  /// <summary>
  /// Constructor
  /// </summary>
  Scene();

  /// <summary>
  /// Initialize the vertex and fragment shader and a program.
  /// </summary>
  /// <param name="vshader_filename"></param>
  /// <param name="fshader_filename"></param>
  /// <returns></returns>
  bool initShaders(const std::string& vshader_filename, const std::string& fshader_filename);

  bool initShadows(const std::string& vshader_filename, const std::string& fshader_filename);

  /// <summary>
  /// Add a lightsource
  /// </summary>
  /// <param name="light">A new light source</param>
  void add(std::shared_ptr<Light>& light);

  void addShadowMap(std::shared_ptr<Light>& light, std::shared_ptr<Camera> camera);

  /// <summary>
  /// Get all light soutces
  /// </summary>
  /// <returns>A vector of lightsources</returns>
  const LightVector& getLights();

  /// <summary>
  /// Get the shader program
  /// </summary>
  /// <returns>The shader program</returns>
  std::vector<GLuint> getPrograms() const;


  GLuint getProgram(int programId);

  /// <summary>
  /// Get the camera
  /// </summary>
  /// <returns>The camera</returns>
  std::shared_ptr<Camera> getCamera(int cameraId = DEFAULT_CAMERA);

  int addCamera(std::shared_ptr<Camera> camera);

  bool selectCamera(int cameraId);

  std::shared_ptr<Camera> getSelectedCamera();

  int getSelectedCameraId();

  ~Scene();

  /// <summary>
  /// Apply the camera
  /// </summary>
  void applyCamera();

  /// <summary>
  /// Use the shader program
  /// </summary>
  void useProgram(int shaderId = DEFAULT_SHADER);

  /// <summary>
  /// Add a new group.
  /// </summary>
  /// <param name="node">A new node</param>
  void add(std::shared_ptr<Group> node, int shape = BOX, bool staticType = false, int shader = DEFAULT_SHADER);



  /// <summary>
  /// Reset all nodes transform to its initial value
  /// </summary>
  void resetTransform();

  const std::shared_ptr<Group> getRoot();

  /// <summary>
  /// Compute a bounding box for the whole scene
  /// </summary>
  /// <returns>A bounding box for the whole scene</returns>
  BoundingBox calculateBoundingBox();

  int addShader(const std::string& vshader_filename, const std::string& fshader_filename);

  /// <summary>
  /// Render the whole scene
  /// </summary>
  void render();

  void createDotFile(std::string fileName);

  void setSkybox(int programId, std::vector<std::string> textures, std::string modelFile);

  void enableShadows(bool enabled);

  std::shared_ptr<Physics> getPhysicsWorld();

  bool shadowsIsEnabled();


  void update(TimeStep ts);

private:
  std::shared_ptr<Physics> m_physics;

  std::vector<GLuint> m_programs;
  std::vector<std::shared_ptr<Camera>> m_cameras;
  unsigned int m_selectedCamera;
  std::shared_ptr<Group> m_root;
  std::shared_ptr<SkyBox> m_skybox;

  bool m_shadowsEnabled;
  std::shared_ptr<ShadowMap> m_shadowMap;
  GLuint m_depthProgram;
  std::shared_ptr<RenderVisitor> m_renderer;
  std::shared_ptr<UpdateVisitor> m_updater;
  GLint m_uniform_numberOfLights;
};

