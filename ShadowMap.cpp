#include "ShadowMap.h"

ShadowMap::ShadowMap(GLuint depthProgram, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light)
{
  m_camera = camera;
  m_light = light;
  //TODO pass this as a parameter somewhere.
  int width = 1920;
  int height = 1080;
  m_depthProgram = depthProgram;
  m_lightType = m_light->getPosition()[3];
  m_shadowMapRender = std::shared_ptr<RenderToTexture>(new RenderToTexture(width, height, depthProgram));
}

bool ShadowMap::init(unsigned int textureSlot)
{
  return m_shadowMapRender->init(textureSlot);
}

/*Update the light position.
* Downside with this is that any light that is
* used to generate shadows wont be able to be move
* with callbacks since this position will potentially be
* overwritten by this method. However this will ensure that the light
* and camera position is synced.  //TODO should probably find a way to 
* determine if this light should update position from here
* or not. 
*/
void ShadowMap::update()
{
  glm::vec3 cameraPos = m_camera->getPosition();
  m_light->setPosition(glm::vec4(cameraPos, m_lightType));
}

void ShadowMap::apply(GLuint renderProgram, std::shared_ptr<Group> startNode)
{
  //Render depth to texture.
  m_shadowMapRender->render(m_camera, startNode);
  std::shared_ptr<Texture> shadowTexture = m_shadowMapRender->getTexture();

  //Bind and apply shadowmap in shader.
  glUseProgram(renderProgram);
  std::string shadowUniform = "shadowMap";
  shadowTexture->bind();
  shadowTexture->apply(renderProgram, shadowUniform.c_str());

  //Check if the light is directional light or other type of light and
  //set the projection matrix.
  glm::mat4 depthProjectionMatrix;
  if(m_lightType == 0.0) //Directional light
  {
    depthProjectionMatrix = m_camera->getOrthoProjection(startNode->getBoundingBox());
  }

  else //Other type of light.
  {
    depthProjectionMatrix = m_camera->getPerspectiveProjection();
  }

  //Compute the View Projection matrix from the lights point of view.
  glm::vec3 cameraPos = m_camera->getPosition();
  glm::vec3 cameraDir = m_camera->getDirection();
  glm::mat4 depthViewMatrix = glm::lookAt(cameraPos, cameraPos + cameraDir, glm::vec3(0,1,0));

  //Add bias matrix
  glm::mat4 biasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
  );

  //Compute the final depth MVP matrix to be used in the shader.
  glm::mat4 depthMVP = biasMatrix * depthProjectionMatrix * depthViewMatrix;

  //Set lights MVP matric in shader.
  std::string uniform = "lightSpaceMatrix";
  GLuint depthMatrixID = glGetUniformLocation(renderProgram, uniform.c_str());
  if(depthMatrixID == -1)
  {
    //std::cout << "-------------------Failed to get " << uniform << " using prorgam: " << renderProgram << std::endl;
    return;
  }
  glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, glm::value_ptr(depthMVP));
}

void ShadowMap::clear()
{
  m_shadowMapRender->clear();
}

