#include "Physics.h"

Physics::Physics()
{
  //TODO might want to pass in parameters or make a way to set settings.
  // Create the world settings 
  reactphysics3d::PhysicsWorld::WorldSettings settings; 
  settings.defaultVelocitySolverNbIterations = 20; 
  settings.isSleepingEnabled = true; 
  settings.gravity = reactphysics3d::Vector3(0, -2.82, 0); 
 
  //Simple test to see if the new physics library is working.
  m_physicsCommon = new reactphysics3d::PhysicsCommon();
  
  // Create a physics world
  m_physicsWorld = m_physicsCommon->createPhysicsWorld(settings);

  m_physicsVisitor = std::shared_ptr<InitPhysicsVisitor>(new InitPhysicsVisitor(m_physicsCommon, m_physicsWorld));

  m_timeStep = 1.0f / 60.0f;
}

void Physics::setDebugMode(bool debug)
{
  m_debugEnabled = debug;
}

bool Physics::debugEnabled()
{
  return m_debugEnabled;
}

bool Physics::init(const std::string& vshader_filename, const std::string& fshader_filename)
{
  /* Compile and link shaders */
  m_program = glCreateProgram();
  GLint link_ok = GL_FALSE;
  GLint validate_ok = GL_FALSE;
  GLuint vs, fs;
  if ((vs = vr::loadShader(vshader_filename, GL_VERTEX_SHADER)) == 0) return false;
  if ((fs = vr::loadShader(fshader_filename, GL_FRAGMENT_SHADER)) == 0) return false;

  glAttachShader(m_program, vs);
  glAttachShader(m_program, fs);
  glLinkProgram(m_program);
  glGetProgramiv(m_program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) 
  {
    fprintf(stderr, "glLinkProgram:");
    std::cout << "\t linking failed" << std::endl;
    vr::printCompilationError(m_program);
    return -1;
  }

  glValidateProgram(m_program);
  glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validate_ok);
  if (!validate_ok) 
  {
    fprintf(stderr, "glValidateProgram:");
    vr::printCompilationError(m_program);
    return -1;
  }  

  //Get vertex position location
  const char* attribute_name;
  attribute_name = "position";
  m_verticesLocation = glGetAttribLocation(m_program, attribute_name);
  if (m_verticesLocation == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return false;
  }

  enableDebug();
  return true;
}

void Physics::add(std::shared_ptr<Group> node, int shape, bool staticBody)
{
  m_physicsVisitor->visit(*node);
}

void Physics::update(Group &group)
{
  m_physicsWorld->update(m_timeStep);
}

void Physics::renderCollisionBoxes(std::shared_ptr<Camera> camera)
{

  //Generate data to draw.
  reactphysics3d::DebugRenderer& debugRenderer = m_physicsWorld->getDebugRenderer();
  debugRenderer.computeDebugRenderingPrimitives(*m_physicsWorld);

  //Get the number of vertices.
  const int nrLines = debugRenderer.getNbLines();
  const int nrTraingles = debugRenderer.getNbTriangles();

  //Fetch triangles
  reactphysics3d::Array<reactphysics3d::DebugRenderer::DebugTriangle> triangles = debugRenderer.getTriangles();
  std::vector<glm::vec3> finalData;
  for(int i = 0; i < triangles.size(); i++)
  {
    const reactphysics3d::Vector3 &p1 = triangles[i].point1;
    const reactphysics3d::Vector3 &p2 = triangles[i].point2;
    const reactphysics3d::Vector3 &p3 = triangles[i].point3;
    
    finalData.push_back(glm::vec3(p1.x, p1.y, p1.z));
    finalData.push_back(glm::vec3(p2.x, p2.y, p2.z));
    finalData.push_back(glm::vec3(p3.x, p3.y, p3.z));
  }

  //Fetch lines.
  std::vector<glm::vec3> finalDataLines;
  if(nrLines > 0)
  {
    const reactphysics3d::DebugRenderer::DebugLine *dataLines = debugRenderer.getLinesArray();
    for(int i = 0; i < nrLines; i++)
    {
      const reactphysics3d::Vector3 &p1 = dataLines[i].point1;
      const reactphysics3d::Vector3 &p2 = dataLines[i].point2;
      finalDataLines.push_back(glm::vec3(p1.x, p1.y, p1.z));
      finalDataLines.push_back(glm::vec3(p2.x, p2.y, p2.z));
    }
  }

  debugRenderer.reset();

  //-----------Opengl rendering starts here.

  glUseProgram(m_program);
  camera->init(m_program);
  camera->applyPerspective(m_program);

  //Create buffer and draw triangles.
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, finalData.size() * sizeof(finalData[0]), finalData.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(m_verticesLocation);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(m_verticesLocation, 3, GL_FLOAT, GL_TRUE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, nrTraingles);
  glEnableVertexAttribArray(0);

  //Create buffer and draw lines.
  if(nrLines > 0)
  {
    GLuint vboLines;
    glGenBuffers(1, &vboLines);
    glBindBuffer(GL_ARRAY_BUFFER, vboLines);
    glBufferData(GL_ARRAY_BUFFER, finalDataLines.size() * sizeof(finalDataLines[0]), finalDataLines.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(m_verticesLocation);
    glBindBuffer(GL_ARRAY_BUFFER, vboLines);
    glVertexAttribPointer(m_verticesLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_LINES, 0, nrLines);
  }
}

void Physics::enableDebug()
{
  m_debugEnabled = true;

  m_physicsWorld->setIsDebugRenderingEnabled(true); 

  // Get a reference to the debug renderer 
  reactphysics3d::DebugRenderer& debugRenderer = m_physicsWorld->getDebugRenderer();

  // Select the contact points and contact normals to be displayed 
  debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true); 
  debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
  debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, false);
  debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, false);

}