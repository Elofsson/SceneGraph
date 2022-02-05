#pragma once

#include <memory>

#include "Material.h"
#include "BoundingBox.h"
#include <glm/glm.hpp>
#include <string>

/// <summary>
/// Simple class that store geometry data and draws it
/// </summary>
class Mesh
{

public:
  typedef std::vector<glm::vec2> vec2Vector;
  typedef std::vector<glm::vec3> vec3Vector;
  typedef std::vector<glm::vec4> vec4Vector;
  typedef std::vector<GLushort> GLushortVector;
  std::string name;


public:
  vec4Vector vertices;
  vec3Vector normals;
  vec2Vector texCoords;
  GLushortVector elements;

  /// <summary>
  /// The transformation matrix that transforms from the local coordinate of the mesh to the world
  /// </summary>
  glm::mat4 object2world;

  /// <summary>
  /// Constructor
  /// </summary>
  /// <param name="useVAO">If true Vertex Array Objects will be used for this mesh</param>
  Mesh(bool useVAO = true);

  //void setMaterial(std::shared_ptr<Material>& material);
  //std::shared_ptr<Material> getMaterial();

  ~Mesh();

  /// <summary>
  /// Initialize the shaders uniforms and attributes
  /// </summary>
  /// <param name="program">The program for which uniforms and attributes will be initialized</param>
  /// <returns></returns>
  bool initShaders(GLint program);

  
  /// <summary>
  /// Store object vertices, normals and/or elements in graphic card buffers
  /// </summary>
  void upload();

  /// <summary>
  /// Render the object
  /// </summary>
  /// <param name="program">Render the mesh using this program</param>
  /// <param name="modelMatrix">The current model matrix</param>
  void render(GLuint program, const glm::mat4& modelMatrix);

  /// <summary>
  /// Calculate and return a bounding box for this geometry based on its vertices
  /// </summary>
  /// <returns>The computed bounding box</returns>
  BoundingBox calculateBoundingBox();


  /// <summary>
  /// Draw object bounding box
  /// </summary>
  void draw_bbox();

private:

  //std::shared_ptr<Material> m_material;

  GLuint m_vbo_vertices, m_vbo_normals, m_vbo_texCoords, m_ibo_elements;
  GLuint m_vao;
  GLint m_attribute_v_coord;
  GLint m_attribute_v_normal;
  GLint m_attribute_v_texCoords;

  GLint m_uniform_m;
  GLint m_uniform_m_3x3_inv_transp;

  bool m_useVAO;
};
typedef std::vector<std::shared_ptr<Mesh> > MeshVector;

