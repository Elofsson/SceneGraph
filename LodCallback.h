#pragma once

#include "Group.h"
#include "UpdateCallback.h"


class Camera;

class LodCallback : public UpdateCallback
{
public:
  LodCallback(std::shared_ptr<Group> lodGroup, std::shared_ptr<Camera> camera);
  virtual void update() override;
private:
  std::shared_ptr<Group> m_group;
  std::shared_ptr<Camera> m_camera;
  BoundingBox m_boundingbox;
};