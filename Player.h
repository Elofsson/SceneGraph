#pragma once

#include <memory>
#include <glm/gtx/io.hpp>

#include "Transform.h"
#include "Camera.h"
#include "PhysicsState.h"

class Player
{
public:
  Player(float speed, std::shared_ptr<Camera> camera);
  void processInput(GLFWwindow* window);
  void setModel(std::shared_ptr<Transform> model, std::shared_ptr<PhysicsState> physics);

private:
  std::shared_ptr<Camera> m_camera;
  std::shared_ptr<Transform> m_player;
  float m_movementSpeed;
  float m_offsetY;
  float m_gravity;
  glm::vec3 m_position;
};