#pragma once

#include "Node.h"
#include "UpdateCallback.h"
#include "PhysicsState.h"
#include <glm/gtx/io.hpp>

class ForceCallback : public UpdateCallback
{

public:
  ForceCallback(std::shared_ptr<PhysicsState> physics, glm::vec3 force);
  void update() override;

private:
  glm::vec3 m_force;
  std::shared_ptr<PhysicsState> m_physics;
};