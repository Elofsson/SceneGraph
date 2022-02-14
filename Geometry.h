#pragma once

#include "Node.h"
#include "NodeVisitor.h"
#include "BoundingBox.h"
#include <glm/glm.hpp>
#include <vr/glErrorUtil.h>

//TODO Implement Geometry.
//TODO Data to contian: Vertices, Vertex colors and Texture Coordinates if present, Normals.

typedef std::vector<glm::vec2> vec2Vector;
typedef std::vector<glm::vec3> vec3Vector;
typedef std::vector<glm::vec4> vec4Vector;
typedef std::vector<GLushort> GLushortVector;

class Geometry : public Node {

public:

  Geometry(bool useVAO = true);

  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;  

  //Store object vertices, normals and/or elements in graphic card buffers
  void upload();

  //Draw this geometry.
  void draw();

  void apply(glm::mat4 transformMatrix);

  void insertVertex(glm::vec4 vertex, int index);
  void insertNormal(glm::vec3 normal, int index);
  void insertTexCoord(glm::vec2 texCoord, int index);
  void insertElement(GLushort element);

  vec4Vector getVertices();
  vec3Vector getNormals();
  vec2Vector getTexCoords();
  GLushortVector getElements();

  //Resize the vertice, normals and texcoord arrays.
  void resize(unsigned int size);

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