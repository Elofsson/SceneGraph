#pragma once

#include "Node.h"
#include "NodeVisitor.h"
#include "BoundingBox.h"
#include <glm/glm.hpp>
#include <vr/glErrorUtil.h>


typedef std::vector<glm::vec2> vec2Vector;
typedef std::vector<glm::vec3> vec3Vector;
typedef std::vector<glm::vec4> vec4Vector;
typedef std::vector<GLushort> GLushortVector;


/**
 * @brief Geometry class responsible for storing
 *        vertices, normals, texturecoordinates 
 *        and indices.
 * 
 */
class Geometry : public Node {

public:

  /**
   * @brief Construct a new Geometry object.
   * 
   * @param useVAO True if Vertex Array Object is to be used.
   */
  Geometry(bool useVAO = true);

  /**
   * @brief Calculates the boundingbox for this geometry
   * 
   * @param modelMat 
   * @return BoundingBox 
   */
  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;  

  /**
   * @brief Store object vertices, normals and/or elements in graphic card buffers
   * 
   */
  void upload();

  /**
   * @brief Draw the geometry
   * 
   */
  virtual void draw();

  /**
   * @brief Set uniforms and locations in the shader.
   * 
   * @param transformMatrix Modelmatrix to be set.
   */
  virtual void apply(glm::mat4 transformMatrix);

  /**
   * @brief Insert a new vertex at the specified index.
   *        NOTE: resize has to be called in order
   *        to not get out of bounds
   * 
   * @param vertex Vertex
   * @param index Index
   */
  void insertVertex(glm::vec4 vertex, int index);

  /**
   * @brief Insert a new normal at the specified index.
   *        NOTE: resize has to be called in order
   *        to not get out of bounds
   * 
   * @param normal Normal
   * @param index index
   */
  void insertNormal(glm::vec3 normal, int index);

  /**
   * @brief Insert a new texture coordinate at the specified index.
   *        NOTE: resize has to be called in order
   *        to not get out of bounds
   * 
   * @param texCoord Texture coordinate
   * @param index index
   */
  void insertTexCoord(glm::vec2 texCoord, int index);

  /**
   * @brief Insert a new indice
   * 
   * @param element new index to vertice list. 
   */
  void insertElement(GLushort element);

  /**
   * @brief Get the Vertices object
   * 
   * @return vec4Vector 
   */
  vec4Vector getVertices();

  /**
   * @brief Get the Normals object
   * 
   * @return vec3Vector 
   */
  vec3Vector getNormals();

  /**
   * @brief Get the Tex Coords object
   * 
   * @return vec2Vector 
   */
  vec2Vector getTexCoords();

  /**
   * @brief Get the Elements object
   * 
   * @return GLushortVector 
   */
  GLushortVector getElements();

  /**
   * @brief Resize the vertice, normals and texcoord arrays.
   *        has to be called before inserting any vertices,
   *        normals or texture coordinates
   * 
   * @param size size of the arrays: vertice, normals, texturecoordinates
   */
  void resize(unsigned int size);

  /**
   * @brief Visit this visitor
   * 
   * @param visitor 
   */
  virtual void accept(NodeVisitor& visitor) override;

  //Initialise shaders with attributes, uniforms e.t.c.
  bool initShaders(GLuint program);

private:
  vec4Vector m_vertices;
  vec3Vector m_normals;
  vec2Vector m_texCoords;
  GLushortVector m_elements;

  //GL attributes.
  GLuint m_vbo_vertices, m_vbo_normals, m_vbo_texCoords, m_ibo_elements;
  GLuint m_vao;
  GLint m_attribute_v_coord;
  GLint m_attribute_v_normal;
  GLint m_attribute_v_texCoords;
  GLuint m_uniform_m_3x3_inv_transp;
  GLuint m_uniform_m;
  
  bool m_useVAO;
}; 

typedef std::vector<std::shared_ptr<Geometry>> GeometryVector;