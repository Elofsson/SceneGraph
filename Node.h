#pragma once

#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "BoundingBox.h"
#include <glm/glm.hpp>

/// <summary>
/// Simple class that store a number of meshes and draws it
/// </summary>
class Node
{

public:
  /// <summary>
  /// Name of the node
  /// </summary>
  std::string name;

  /// <summary>
  /// Transformation for the nodes local coordinate system to the world
  /// </summary>
  glm::mat4 object2world;

  /// <summary>
  /// Constructor
  /// </summary>
  Node();

  /// <summary>
  /// Get all meshes
  /// </summary>
  /// <returns>A vector of meshes</returns>
  MeshVector& getMeshes();

  /// <summary>
  /// Add a mesh to the vector of meshes
  /// </summary>
  /// <param name="mesh">A new mesh</param>
  void add(std::shared_ptr<Mesh>& mesh);

  /// <summary>
  /// Set an initial transformation that can be reset at a later point in time
  /// </summary>
  /// <param name="m"></param>
  void setInitialTransform(const glm::mat4& m);

  ~Node();

  void resetTransform();

  
  /// <summary>
  /// Draw the node (all of its meshes)
  /// </summary>
  /// <param name="program">The active program for which rendering will be performed</param>
  void render(GLuint program);

  /// Calculate and return a bounding box for this Node based on its Mesh objects
  BoundingBox calculateBoundingBox();

private:

  MeshVector m_meshes;
  glm::mat4 m_initialTransform;
 
};
typedef std::vector<std::shared_ptr<Node> > NodeVector;
