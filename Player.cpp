#include "Player.h"

Player::Player(float speed, std::shared_ptr<Camera> camera)
{
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

std::shared_ptr<Group> Player::processInput(GLFWwindow *window)
{
  m_camera->processInput(window);
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
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
      std::cout << "Shoot " << std::endl;
      glm::vec3 trajectoryVelocity = m_camera->getDirection() * 3.0f;
      
      //Create new trajectory
      std::shared_ptr<Transform> trajectory = std::shared_ptr<Transform>(new Transform(bodyPosition.x, bodyPosition.y, bodyPosition.z));
      std::shared_ptr<PhysicsState> trajectoryPhysics = std::shared_ptr<PhysicsState>(new PhysicsState);
      trajectoryPhysics->setShape(SHAPE_SPHERE);
      trajectoryPhysics->setType(reactphysics3d::BodyType::DYNAMIC);
      trajectoryPhysics->setMass(0.1);
      trajectory->setPhysics(trajectoryPhysics);

      //Add model to trajectory.
      trajectory->addChild(m_trajectoryModel);

      //Create force update callback.
      std::shared_ptr<ForceCallback> projectileForceCallback = std::shared_ptr<ForceCallback>(new ForceCallback(trajectoryPhysics, trajectoryVelocity));
      trajectory->addCallback(projectileForceCallback);

      //this group is only created to avoid visitor bug. This should be fixed.
      std::shared_ptr<Group> group = std::shared_ptr<Group>(new Group());
      group->addChild(trajectory); 

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