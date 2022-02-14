#include "Geometry.h"
#include "NodeVisitor.h"


Geometry::Geometry(bool useVAO) {
  m_useVAO = useVAO;
}

BoundingBox Geometry::calculateBoundingBox(glm::mat4 modelMat) {
  BoundingBox box;
  for(auto v : m_vertices)
  {
    glm::vec3 vTransformed = modelMat * v;
    box.expand(vTransformed);
  }

  return box;
}

void Geometry::accept(NodeVisitor &visitor)
{
  if(isEnabled())
  {
    visitor.visit(*this);
  }
}

void Geometry::draw() {
  if (m_useVAO) {
    glBindVertexArray(m_vao);
    CHECK_GL_ERROR_LINE_FILE();
  }
  
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

      GLuint size = GLuint(m_elements.size());
      glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
      CHECK_GL_ERROR_LINE_FILE();
  }
  else {
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());
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

  if (m_vertices.size() > 0) {
    glGenBuffers(1, &this->m_vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]),
      m_vertices.data(), GL_STATIC_DRAW);
    CHECK_GL_ERROR_LINE_FILE();
  }

   if (m_normals.size() > 0) {
      glGenBuffers(1, &this->m_vbo_normals);
      glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_normals);
      glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(m_normals[0]),
        m_normals.data(), GL_STATIC_DRAW);
      CHECK_GL_ERROR_LINE_FILE();
   }

   if (m_texCoords.size() > 0) {
     glGenBuffers(1, &this->m_vbo_texCoords);
     glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo_texCoords);
     glBufferData(GL_ARRAY_BUFFER, m_texCoords.size() * sizeof(m_texCoords[0]),
       m_texCoords.data(), GL_STATIC_DRAW);
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

  if (m_elements.size() > 0) {
    glGenBuffers(1, &this->m_ibo_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elements.size() * sizeof(m_elements[0]),
      m_elements.data(), GL_STATIC_DRAW);
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

void Geometry::apply(glm::mat4 transformMatrix)
{

  glUniformMatrix4fv(m_uniform_m, 1, GL_FALSE, glm::value_ptr(transformMatrix));

  	/* Transform normal vectors with transpose of inverse of upper left
	3x3 model matrix (ex-gl_NormalMatrix): */
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(transformMatrix)));
	glUniformMatrix3fv(m_uniform_m_3x3_inv_transp, 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));
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

  const char* uniform_name;
	uniform_name = "m";
	m_uniform_m = glGetUniformLocation(program, uniform_name);
	if (m_uniform_m == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

	//Get the location for normal matrix.
	uniform_name = "m_3x3_inv_transp";
	m_uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
	if (m_uniform_m_3x3_inv_transp == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

  return true;
}


void Geometry::resize(unsigned int size)
{
  m_vertices.resize(size);
  m_normals.resize(size);
  m_texCoords.resize(size);
}

void Geometry::insertVertex(glm::vec4 vertex, int index)
{
  m_vertices[index] = vertex;
}

void Geometry::insertNormal(glm::vec3 normal, int index)
{
  m_normals[index] = normal;
}

void Geometry::insertTexCoord(glm::vec2 texCoord, int index)
{
  m_texCoords[index] = texCoord;
}

void Geometry::insertElement(GLushort element)
{
  m_elements.push_back(element);
}

vec4Vector Geometry::getVertices()
{
  return m_vertices;
}

vec3Vector Geometry::getNormals()
{
  return m_normals;
}

vec2Vector Geometry::getTexCoords()
{
  return m_texCoords;
}

GLushortVector Geometry::getElements()
{
  return m_elements;
}

