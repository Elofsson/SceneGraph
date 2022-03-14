#pragma once

#include "UpdateCallback.h"
#include "Transform.h"
#include "PhysicsState.h"
#include <glm/gtx/io.hpp>

class PhysicsCallback : public UpdateCallback
{
public:
  PhysicsCallback(Transform *transform, std::shared_ptr<PhysicsState> physics);
  virtual void update() override;

private:
  Transform* m_transform;
  std::shared_ptr<PhysicsState> m_physicsState;
  glm::vec3 m_physicLocalPos;

};