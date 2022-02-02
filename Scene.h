
#pragma once

#include <memory>
#include <vector>
#include <sstream>
#include "Node.h"
#include "Light.h"
#include "Camera.h"
class Scene;

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

  /// <summary>
  /// Add a lightsource
  /// </summary>
  /// <param name="light">A new light source</param>
  void add(std::shared_ptr<Light>& light);

  /// <summary>
  /// Get all light soutces
  /// </summary>
  /// <returns>A vector of lightsources</returns>
  const LightVector& getLights();

  /// <summary>
  /// Get the shader program
  /// </summary>
  /// <returns>The shader program</returns>
  GLuint getProgram() const;

  /// <summary>
  /// Get the camera
  /// </summary>
  /// <returns>The camera</returns>
  std::shared_ptr<Camera> getCamera();

  ~Scene();

  /// <summary>
  /// Apply the camera
  /// </summary>
  void applyCamera();

  /// <summary>
  /// Use the shader program
  /// </summary>
  void useProgram();

  /// <summary>
  /// Add a new node
  /// </summary>
  /// <param name="node">A new node</param>
  void add(std::shared_ptr<Node>& node);

  /// <summary>
  /// Reset all nodes transform to its initial value
  /// </summary>
  void resetTransform();

  /// <summary>
  /// Get a all nodes
  /// </summary>
  /// <returns>A vector containing all nodes</returns>
  const NodeVector& getNodes();

  /// <summary>
  /// Get the i:th node
  /// </summary>
  /// <param name="i">Index in vector</param>
  /// <returns>A node</returns>
  std::shared_ptr<Node> getNode(size_t i);

  /// <summary>
  /// Compute a bounding box for the whole scene
  /// </summary>
  /// <returns>A bounding box for the whole scene</returns>
  BoundingBox calculateBoundingBox();

  /// <summary>
  /// Render the whole scene
  /// </summary>
  void render();

private:
  NodeVector m_nodes;
  LightVector m_lights;
  GLuint m_program;
  GLint m_uniform_numberOfLights;

  std::shared_ptr<Camera> m_camera;
};

