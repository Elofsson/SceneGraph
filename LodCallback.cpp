#include "LodCallback.h"
#include "Camera.h"
#include <iostream>

LodCallback::LodCallback(std::shared_ptr<Group> lodGroup, std::shared_ptr<Camera> camera)
{
  m_group = lodGroup;
  m_camera = camera;
  m_boundingbox = lodGroup->calculateBoundingBox(glm::mat4(1.0f));
}


void LodCallback::update()
{
  glm::vec3 cameraPos = m_camera->getPosition();
  float objectCameraDiff =  glm::distance(m_boundingbox.getCenter(), cameraPos);
  float levelIncrease = m_boundingbox.getRadius();
  float currentLevel = levelIncrease;

  NodeVector children = m_group->getChildren();
  bool found = false;
  for(int i = 0; i < children.size(); i++)
  {
    if(currentLevel >= objectCameraDiff && !found)
    {
      children[i]->setEnabled(true);
      found = true;
    }

    else
    {
      children[i]->setEnabled(false);
    }
    currentLevel += levelIncrease;
  }
}