#pragma once

#include "RenderToTexture.h"
#include "Camera.h"

class ShadowMap
{

public:
  ShadowMap(GLuint depthProgram, std::shared_ptr<Camera> camera, std::shared_ptr<Light> light);
  bool init(unsigned int textureSlot);
  void apply(GLuint program, std::shared_ptr<Group> node);
  void clear();
  void update();

private:
  std::shared_ptr<Camera> m_camera;
  std::shared_ptr<Light> m_light;
  std::shared_ptr<RenderToTexture> m_shadowMapRender;
  GLuint m_depthProgram;
  int m_lightType;
};