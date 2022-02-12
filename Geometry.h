#pragma once

#include "Node.h"
#include "NodeVisitor.h"
#include "BoundingBox.h"
#include <glm/glm.hpp>
#include <vr/glErrorUtil.h>

//TODO Implement Geometry.
//TODO Data to contian: Vertices, Vertex colors and Texture Coordinates if present, Normals.


class Geometry : public Node {

public:
  typedef std::vector<glm::vec2> vec2Vector;
  typedef std::vector<glm::vec3> vec3Vector;
  typedef std::vector<glm::vec4> vec4Vector;
  typedef std::vector<GLushort> GLushortVector;

  //TODO Consider making this private.
  vec4Vector vertices;
  vec3Vector normals;
  vec2Vector texCoords;
  GLushortVector elements;

  Geometry(bool useVAO = true);

  virtual BoundingBox calculateBoundingBox(glm::mat4 modelMat) override;
  

  //Store object vertices, normals and/or elements in graphic card buffers
  void upload();

  //Draw this geometry.
  void draw();

  virtual void accept(NodeVisitor& visitor) override;

  //Initialise shaders with attributes, uniforms e.t.c.
  bool initShaders(GLuint program);

private:
  //GL attributes.
  GLuint m_vbo_vertices, m_vbo_normals, m_vbo_texCoords, m_ibo_elements;
  GLuint m_vao;
  GLint m_attribute_v_coord;
  GLint m_attribute_v_normal;
  GLint m_attribute_v_texCoords;
  
  bool m_useVAO;
}; 

typedef std::vector<std::shared_ptr<Geometry>> GeometryVector;