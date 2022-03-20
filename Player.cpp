#include "Player.h"

Player::Player(float speed, std::shared_ptr<Camera> camera)
{
  m_fireRate = 0.25f;
  m_lastShot = 1.0f;
  m_movementSpeed = speed;
  m_camera = camera;
  m_position = camera->getPosition();
}

void Player::setModel(std::shared_ptr<Transform> model, std::shared_ptr<PhysicsState> physics)
{
  m_player = model;
  BoundingBox box = m_player->calculateBoundingBox(glm::mat4(1.0f));
  m_offsetY = box.getRadius() * 1.5;
  m_player->setPhysics(physics);
}

std::shared_ptr<Group> Player::processInput(GLFWwindow *window, TimeStep ts)
{
  m_camera->processInput(window, ts);
  glm::vec3 cameraPos = m_camera->getPosition();

  //Update camera position.
  reactphysics3d::RigidBody* body = m_player->getPhysics()->getBody();
  const reactphysics3d::Vector3& position = body->getTransform().getPosition();
  glm::vec3 bodyPosition = glm::vec3(position.x, position.y + m_offsetY, position.z);
  m_camera->setPosition(bodyPosition);

  glm::vec3 velocity = (cameraPos - bodyPosition) * m_movementSpeed;
  m_position += velocity;

  //std::cout << "Velocity: " << velocity << std::endl;
  reactphysics3d::Vector3 previousForce = body->getForce();
  reactphysics3d::Vector3 force(velocity.x + previousForce[0], 0, velocity.z + previousForce[2]);

  //Jump.
  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  { 
    std::cout << "Jumping " << std::endl;
    force[1] = glm::abs((velocity.y));
  }

  //Apply force.
  body->applyWorldForceAtCenterOfMass(force);

  //Check for butten press, shoot.

  if(m_trajectoryModel != nullptr)
  {
    m_lastShot += ts;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && m_lastShot >= m_fireRate)
    {
      std::cout << "Shoot " << std::endl;
      glm::vec3 trajectoryVelocity = m_camera->getDirection() * 50.0f;
      
      //Create new trajectory
      std::shared_ptr<Transform> trajectory = std::shared_ptr<Transform>(new Transform(bodyPosition.x, bodyPosition.y, bodyPosition.z));
      std::shared_ptr<PhysicsState> trajectoryPhysics = std::shared_ptr<PhysicsState>(new PhysicsState);
      trajectoryPhysics->setShape(SHAPE_SPHERE);
      trajectoryPhysics->setType(reactphysics3d::BodyType::DYNAMIC);
      trajectoryPhysics->setMass(0.15);
      trajectoryPhysics->setBounciness(0.9);
      trajectoryPhysics->setForce(reactphysics3d::Vector3(trajectoryVelocity.x, trajectoryVelocity.y, trajectoryVelocity.z));
      trajectory->setPhysics(trajectoryPhysics);

      //Add model to trajectory.
      trajectory->addChild(m_trajectoryModel);
      
      //this group is only created to avoid visitor bug. This should be fixed.
      std::shared_ptr<Group> group = std::shared_ptr<Group>(new Group());
      group->addChild(trajectory); 

      m_lastShot = 0.0f;
      return group;
    }
  }

  return nullptr;
}

//First implementation of a weapon. A weapon should be a separate class later.
void Player::setWeapon(std::shared_ptr<Group> trajectoryModel)
{
  m_trajectoryModel = trajectoryModel;
}