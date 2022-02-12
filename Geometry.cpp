#include "Geometry.h"
#include "NodeVisitor.h"


Geometry::Geometry(bool useVAO) {
  m_useVAO = useVAO;
}

BoundingBox Geometry::calculateBoundingBox(glm::mat4 modelMat) {
  BoundingBox box;
  for(auto v : vertices)
  {
    glm::vec3 vTransformed = modelMat * v;
    box.expand(vTransformed);
  }

  return box;
}

void Geometry::accept(NodeVisitor &visitor)
{
  visitor.visit(*this);
}

void Geometry::draw() {
  if (m_useVAO) {
    glBindVertexArray(m_vao);
    CHECK_GL_ERROR_LINE_FILE();
  }

  //FIXME see where these should go.
  //if (normals.size() == 0)
  //{
    //draw_bbox();
    //return;
  //}
  
  CHECK_GL_ERROR_LINE_FILE();

  if (!m_useVAO)
  {
    if (this->m_vbo_vertices != 0) 
    {
      glEnableVertexAttribArray(m_attribute_v_coord);
      glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_vertices);
      glVertexAttribPointer(
        m_attribute_v_coord,// attribute
        4,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
        );
    }

    if (this->m_vbo_normals != 0)
    {
      glEnableVertexAttribArray(m_attribute_v_normal);
      glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_normals);
      glVertexAttribPointer(
        m_attribute_v_normal, // attribute
        3,                  // number of elements per vertex, here (x,y,z)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
      );
    }
    if (this->m_vbo_texCoords != 0)
    {
      glEnableVertexAttribArray(m_attribute_v_texCoords);
      glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_texCoords);
      glVertexAttribPointer(
        m_attribute_v_texCoords, // attribute
        2,                  // number of elements per vertex, here (x,y,z)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
      );
    }
  }
  else {
    glEnableVertexAttribArray(m_attribute_v_coord);
    CHECK_GL_ERROR_LINE_FILE();
    glEnableVertexAttribArray(m_attribute_v_normal);
    CHECK_GL_ERROR_LINE_FILE();
    if (m_vbo_texCoords != 0)
      glEnableVertexAttribArray(m_attribute_v_texCoords);
    CHECK_GL_ERROR_LINE_FILE();
    
  }
  CHECK_GL_ERROR_LINE_FILE();

  /* Push each element in buffer_vertices to the vertex shader */
  if (this->m_ibo_elements != 0) 
  {
    if (!m_useVAO)
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo_elements);

      GLuint size = GLuint(this->elements.size());
      glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
      CHECK_GL_ERROR_LINE_FILE();
  }
  else {
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)this->vertices.size());
  }

  if (this->m_vbo_normals != 0)
    glDisableVertexAttribArray(m_attribute_v_normal);

  if (this->m_vbo_vertices != 0)
    glDisableVertexAttribArray(m_attribute_v_coord);

  if (this->m_vbo_texCoords != 0)
    glDisableVertexAttribArray(m_attribute_v_texCoords);

  if (m_useVAO)
    glBindVertexArray(0);
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

  return true;
}
