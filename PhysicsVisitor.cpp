#include "PhysicsVisitor.h"


PhysicsVisitor::PhysicsVisitor()
{
}


void PhysicsVisitor::visit(Group &g)
{
  updatePhysics(g);
  NodeVisitor::traverse(g);
}

void PhysicsVisitor::visit(Transform &t)
{
  updatePhysics(t);

  //Update transform with physics properties here.
  
  /*std::cout << "Bruh " << std::endl;
  if(m_currentPhysics != nullptr)
  {
    reactphysics3d::RigidBody *body = m_currentPhysics->getBody();
    const reactphysics3d::Transform& transform = body->getTransform();
    const reactphysics3d::Matrix3x3 orientationMatrix = transform.getOrientation().getMatrix();
    const reactphysics3d::Vector3& position = transform.getPosition();
    std::cout << "Position " << position.x << " : " << position.y << " : " << position.z << std::endl;
	  //std::cout << "Object 2 world: [" << object2world[3][0] << ", " << object2world[3][1] << ", " << object2world[3][2] << " ]" << std::endl; 
	  //std::cout << "object2world BEFORE physics" << object2world << std::endl;

    //t.setPosition(glm::vec3(position.x, position.y, position.z));

    float matrix[16]; 
    transform.getOpenGLMatrix(matrix);
	  glm::mat4 translation = glm::make_mat4(matrix);
    t.object2world = translation * t.object2world;
  }*/

  NodeVisitor::traverse(t);
}

void PhysicsVisitor::visit(Geometry &g)
{
  //Currently no operation has to be done on geometries.
}

void PhysicsVisitor::updatePhysics(Node &g)
{
  if(g.getPhysics() != nullptr)
  {
    m_currentPhysics = g.getPhysics(); 
  }
}