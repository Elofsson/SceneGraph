#include "InitPhysicsVisitor.h"
#include <glm/gtx/matrix_decompose.hpp> 
#include <glm/gtx/quaternion.hpp>

InitPhysicsVisitor::InitPhysicsVisitor(reactphysics3d::PhysicsCommon *physicsCommon, reactphysics3d::PhysicsWorld* world)
{
  m_physicsCommon = physicsCommon;
  m_physicsWorld = world;
  m_static = false;
}

void InitPhysicsVisitor::visit(Group &g)
{
  NodeVisitor::traverse(g);

  //m_currentPhysics = nullptr;
}

void InitPhysicsVisitor::visit(Transform &t) 
{
  std::cout << "Visiting transform " << t.name << std::endl;

  //Push on stack.
	if(m_transformStack.empty())
  {
    m_transformStack.push(t.object2world);
  }

  //calculate and concat matrix.
  else
  {
    glm::mat4 prevMat = m_transformStack.top();
    glm::mat4 newObject2world = prevMat * t.object2world;
    m_transformStack.push(newObject2world); 
  }

  if(t.getPhysics() != nullptr)
  {
    m_transformObjStack.push(&t);
  }

  NodeVisitor::traverse(t);

  if(t.getPhysics() != nullptr)
  {
    m_transformObjStack.pop();
  }

  //Pop stack.
	m_transformStack.pop();
}

void InitPhysicsVisitor::visit(Geometry &g)
{
  //initPhysics(g); 
  if(!m_transformObjStack.empty())
  {
    
    //Get the scale of the geometry.
    float x = m_transformStack.top()[0][0];
    float y = m_transformStack.top()[1][1];
    float z = m_transformStack.top()[2][2];
    glm::vec3 scale = glm::vec3(x, y, z);

    Transform *t = m_transformObjStack.top();
    auto physicsState = initPhysics(*t, scale);
    std::shared_ptr<PhysicsCallback> physicsCallback = std::shared_ptr<PhysicsCallback>(new PhysicsCallback(t, physicsState));
    t->addCallback(physicsCallback);
    std::cout << "\t--------------------Init physics callback for transform: " << t->name << " : address " << t << std::endl;
  }
}

void InitPhysicsVisitor::initStaticBodies(bool staticBodies)
{
  m_static = staticBodies;
}

std::shared_ptr<PhysicsState> InitPhysicsVisitor::initPhysics(Transform &t, glm::vec3 scale)
{
  //Do not init physics if no physic state is set.
  glm::mat4 stackTransform =  m_transformStack.top() ;
  std::cout << "Transform " << stackTransform << std::endl;

  BoundingBox box = t.calculateBoundingBox(glm::mat4(1.0f));
  float radius = box.getRadius();
  glm::vec4 bodyPosition = stackTransform * glm::vec4(0, 0, 0, 1);

  //Create rigid body.
  reactphysics3d::Vector3 position(bodyPosition.x, bodyPosition.y, bodyPosition.z);
  reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
  reactphysics3d::Transform transform(position, orientation);  
  reactphysics3d::RigidBody *body = m_physicsWorld->createRigidBody(transform);

  //Create collisionbox.
  reactphysics3d::Collider* collider;
  reactphysics3d::Transform colliderTransform(reactphysics3d::Vector3(0.0, 0.0, 0.0), orientation);

  if(t.getPhysics()->getShape() == SHAPE_BOX)
  {
    const reactphysics3d::Vector3 halfExtents(stackTransform[0][0] / 2, stackTransform[1][1] / 2, stackTransform[2][2] / 2); 
    reactphysics3d::CollisionShape* boxShape = m_physicsCommon->createBoxShape(halfExtents);
    collider = body->addCollider(boxShape, colliderTransform);
  }

  else if(t.getPhysics()->getShape() == SHAPE_SPHERE)
  {
    reactphysics3d::CollisionShape* boxShape = m_physicsCommon->createSphereShape(radius);
    collider = body->addCollider(boxShape, colliderTransform);
  }

  //Update center of mass and other properties.
  body->updateMassPropertiesFromColliders();

  //Update physics state.
  std::shared_ptr<PhysicsState> physicState = t.getPhysics();
  physicState->setCollider(collider);
  physicState->setBody(body);
  physicState->init();
  return physicState;
}