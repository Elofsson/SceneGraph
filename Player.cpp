#include "Player.h"

Player::Player(float speed, std::shared_ptr<Camera> camera)
{
  m_movementSpeed = speed;
  m_camera = camera ;
}

void Player::setModel(std::shared_ptr<Transform> model, std::shared_ptr<PhysicsState> physics)
{
  m_player = model;
  BoundingBox box = m_player->calculateBoundingBox(glm::mat4(1.0f));
  m_offsetY = box.getRadius() * 1.5;
  m_player->setPhysics(physics);

  //m_gravity = -5;//physics->getBody()->getLinearVelocity()[1];
}

void Player::processInput(GLFWwindow *window)
{
  m_camera->processInput(window);
  glm::vec3 cameraPos = m_camera->getPosition();

  //Update camera position.
  reactphysics3d::RigidBody* body = m_player->getPhysics()->getBody();
  const reactphysics3d::Vector3& position = body->getTransform().getPosition();
  glm::vec3 bodyPosition = glm::vec3(position.x, position.y + m_offsetY, position.z);
  m_camera->setPosition(bodyPosition);

  glm::vec3 velocity = (cameraPos - bodyPosition) * m_movementSpeed;

  std::cout << "Velocity: " << velocity << std::endl;
  reactphysics3d::Vector3 previousForce = body->getForce();
  reactphysics3d::Vector3 force(velocity.x + previousForce[0], 0, velocity.z + previousForce[2]);

  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  { 
    force[1] = glm::abs(velocity.y + previousForce[1]);
  }

  body->applyWorldForceAtCenterOfMass(force);
}