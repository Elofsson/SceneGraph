#include "InitPhysicsVisitor.h"
#include <glm/gtx/matrix_decompose.hpp> 
#include <glm/gtx/quaternion.hpp>

InitPhysicsVisitor::InitPhysicsVisitor(reactphysics3d::PhysicsCommon *physicsCommon, reactphysics3d::PhysicsWorld* world)
{
  m_physicsCommon = physicsCommon;
  m_physicsWorld = world;
}

void InitPhysicsVisitor::visit(Group &g)
{
  NodeVisitor::traverse(g);
}

void InitPhysicsVisitor::visit(Transform &t) 
{
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

  //Only push transforms containing physics.
  if(t.getPhysics() != nullptr)
  {
    m_transformObjStack.push(&t);
  }

  NodeVisitor::traverse(t);

  //Only pop when transform has been pushed.
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
    //TODO investigate if the geometries boundingbox is actually needed, 
    //or if the whole transforms boundingbox can be used.
    BoundingBox box = g.calculateBoundingBox(m_transformStack.top());
    Transform *t = m_transformObjStack.top();
    auto physicsState = initPhysics(*t, box);
    if(!physicsState)
    {
      std::cout << "Failed to init physic state." << std::endl;
    }

    else
    {
    std::shared_ptr<PhysicsCallback> physicsCallback = std::shared_ptr<PhysicsCallback>(new PhysicsCallback(t, physicsState));
    t->addCallback(physicsCallback);
    std::cout << "\t--------------------Init physics callback for transform: " << t->name << " : address " << t << std::endl;
    }
  }
}

std::shared_ptr<PhysicsState> InitPhysicsVisitor::initPhysics(Transform &t, BoundingBox box)
{
  //Get the physics state to init.
  std::shared_ptr<PhysicsState> physicState = t.getPhysics();
  if(!physicState)
    return nullptr;

  //Retrieve center position of object and get bodyPosition through the latest transform.
  glm::mat4 stackTransform =  m_transformStack.top();
  glm::vec3 center = box.getCenter();
  glm::vec4 bodyPosition = stackTransform * glm::vec4(0, 0, 0, 1);

  //Default orientation.
  reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();

  //Create rigid body.
  //Reuse rigid body if one is already created.
  if(!physicState->getBody())
  {
    reactphysics3d::Vector3 position(bodyPosition.x, bodyPosition.y, bodyPosition.z);
    reactphysics3d::Transform transform(position, orientation);  
    reactphysics3d::RigidBody *body = m_physicsWorld->createRigidBody(transform);
    physicState->setBody(body);
  }

  reactphysics3d::RigidBody *physicsBody = physicState->getBody();

  //Create collision transformation relative to rigid body.
  glm::vec3 collisionBodyOffset = center - glm::vec3(bodyPosition);
  reactphysics3d::Collider* collider;
  reactphysics3d::Transform colliderTransform(reactphysics3d::Vector3(collisionBodyOffset.x, collisionBodyOffset.y, collisionBodyOffset.z), orientation);
  int shape = t.getPhysics()->getShape();
  if(shape == SHAPE_BOX)
  {
    //Calculate the size of the collision box.
    glm::vec3 min = box.min();
    glm::vec3 max = box.max();
    glm::vec3 size = (max - min);
    size = size * 0.5f;

    const reactphysics3d::Vector3 halfExtents(size.x, size.y, size.z); 
    reactphysics3d::CollisionShape* boxShape = m_physicsCommon->createBoxShape(halfExtents);
    collider = physicsBody->addCollider(boxShape, colliderTransform);
  }

  else if(shape == SHAPE_SPHERE)
  {
    float radius = box.getRadius();
    reactphysics3d::CollisionShape* boxShape = m_physicsCommon->createSphereShape(radius);
    collider = physicsBody->addCollider(boxShape, colliderTransform);
  }

  //Update center of mass and other properties such as friction.
  physicsBody->updateMassPropertiesFromColliders();
  physicState->addCollider(collider);
  physicState->init();

  return physicState;
}