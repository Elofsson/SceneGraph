#include "Geometry.h"
#include "NodeVisitor.h"


Geometry::Geometry(bool useVAO) {
  m_useVAO = useVAO;
}

BoundingBox Geometry::calculateBoundingBox(MeshVector meshVec) {

}

void Geometry::accept(NodeVisitor &visitor)
{
  std::cout << "Geometry::accept " << name << std::endl;
  visitor.visit(*this);
}

void Geometry::draw() {
  std::cout << "Draw geometry: " << name << std::endl;
}

/**
* Store object vertices, normals and/or elements in graphic card
* buffers
*/
void Geometry::upload() 
{
  if (m_useVAO)
  {
    // Create a Vertex Array Object that will handle all VBO:s of this Mesh
    glGenVertexArrays(1, &m_vao);
    CHECK_GL_ERROR_LINE_FILE();
    glBindVertexArray(m_vao);
    CHECK_GL_ERROR_LINE_FILE();
  }

  if (this->vertices.size() > 0) {
    glGenBuffers(1, &this->m_vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(this->vertices[0]),
      this->vertices.data(), GL_STATIC_DRAW);
    CHECK_GL_ERROR_LINE_FILE();
  }

   if (this->normals.size() > 0) {
      glGenBuffers(1, &this->m_vbo_normals);
      glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_normals);
      glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(this->normals[0]),
        this->normals.data(), GL_STATIC_DRAW);
      CHECK_GL_ERROR_LINE_FILE();
   }

   if (this->texCoords.size() > 0) {
     glGenBuffers(1, &this->m_vbo_texCoords);
     glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_texCoords);
     glBufferData(GL_ARRAY_BUFFER, this->texCoords.size() * sizeof(this->texCoords[0]),
       this->texCoords.data(), GL_STATIC_DRAW);
     CHECK_GL_ERROR_LINE_FILE();
   }

   if (m_useVAO)
   {
     glEnableVertexAttribArray(m_attribute_v_coord);
     glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
     glVertexAttribPointer(
       m_attribute_v_coord,  // attribute
       4,                  // number of elements per vertex, here (x,y,z,w)
       GL_FLOAT,           // the type of each element
       GL_FALSE,           // take our values as-is
       0,                  // no extra data between each position
       0                   // offset of first element
     );
     glDisableVertexAttribArray(m_attribute_v_coord);

     glEnableVertexAttribArray(m_attribute_v_normal);
     glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
     glVertexAttribPointer(
       m_attribute_v_normal, // attribute
       3,                  // number of elements per vertex, here (x,y,z)
       GL_FLOAT,           // the type of each element
       GL_FALSE,           // take our values as-is
       0,                  // no extra data between each position
       0                   // offset of first element
     );
     glDisableVertexAttribArray(m_attribute_v_normal);

     glEnableVertexAttribArray(m_attribute_v_texCoords);
     glBindBuffer(GL_ARRAY_BUFFER, m_vbo_texCoords);
     glVertexAttribPointer(
       m_attribute_v_texCoords, // attribute
       2,                  // number of elements per vertex, here (x,y)
       GL_FLOAT,           // the type of each element
       GL_FALSE,           // take our values as-is
       0,                  // no extra data between each position
       0                   // offset of first element
     );
     glDisableVertexAttribArray(m_attribute_v_texCoords);

   }

  if (this->elements.size() > 0) {
    glGenBuffers(1, &this->m_ibo_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(this->elements[0]),
      this->elements.data(), GL_STATIC_DRAW);
  }

  CHECK_GL_ERROR_LINE_FILE();

  if (m_useVAO)
  {
    // Now release VAO
    glEnableVertexAttribArray(0);  // Disable our Vertex Array Object  
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    CHECK_GL_ERROR_LINE_FILE();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}

bool Geometry::initShaders(GLuint program)
{
   const char* attribute_name;
  attribute_name = "vertex.position";
  m_attribute_v_coord = glGetAttribLocation(program, attribute_name);
  if (m_attribute_v_coord == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return false;
  }
  attribute_name = "vertex.normal";
  m_attribute_v_normal = glGetAttribLocation(program, attribute_name);
  if (m_attribute_v_normal == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return false;
  }

  attribute_name = "vertex.texCoord";
  m_attribute_v_texCoords = glGetAttribLocation(program, attribute_name);
  if (m_attribute_v_texCoords == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return false;
  }

  //FIXME check where this model matrix uniform should be set.
  //const char* uniform_name;
  //uniform_name = "m";
  //m_uniform_m = glGetUniformLocation(program, uniform_name);
  //if (m_uniform_m == -1) {
  //  fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
  //  return 0;
  //}

  //FIXME check where this inverse transpose matrix should be set.
  //uniform_name = "m_3x3_inv_transp";
  //m_uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
  //if (m_uniform_m_3x3_inv_transp == -1) {
  //  fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
  //  return false;
  //}

  return true;
}