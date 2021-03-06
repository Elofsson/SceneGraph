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
    auto physicsState = initPhysics(*t, box, g);
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

std::shared_ptr<PhysicsState> InitPhysicsVisitor::initPhysics(Transform &t, BoundingBox box, Geometry &g)
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

  //Decompose transform to get the rotation.
  glm::vec3 scale;
  glm::quat rotation;
  glm::vec3 translation;
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(stackTransform, scale, rotation, translation, skew, perspective);
  
  rotation = glm::conjugate(rotation);

  //Create collision transformation relative to rigid body.
  glm::vec3 collisionBodyOffset = center - glm::vec3(bodyPosition);
  reactphysics3d::Collider* collider;
  reactphysics3d::Quaternion colliderOrientation(rotation.x, rotation.y, rotation.z, rotation.w);
  reactphysics3d::Transform colliderTransform(reactphysics3d::Vector3(collisionBodyOffset.x, collisionBodyOffset.y, collisionBodyOffset.z), colliderOrientation);
  
  //Create box shaped collision.
  int shape = t.getPhysics()->getShape();
  if(shape == SHAPE_BOX)
  {
    //Calculate the size of the collision box.
    //Use boundingbox from geometries local space to get the dimensions.
    BoundingBox geometryBoundingBox = g.calculateBoundingBox(glm::mat4(1.0f));
    glm::vec3 min = scale * geometryBoundingBox.min();
    glm::vec3 max = scale * geometryBoundingBox.max();
    glm::vec3 size = (max - min);
    size = glm::abs(size * 0.5f);

    const reactphysics3d::Vector3 halfExtents(size.x, size.y, size.z); 
    reactphysics3d::CollisionShape* boxShape = m_physicsCommon->createBoxShape(halfExtents);
    collider = physicsBody->addCollider(boxShape, colliderTransform);
  }

  //Create sphere shaped collider
  else if(shape == SHAPE_SPHERE)
  {
    float radius = box.getRadius() / 2;
    reactphysics3d::CollisionShape* boxShape = m_physicsCommon->createSphereShape(radius);
    collider = physicsBody->addCollider(boxShape, colliderTransform);
  }

  //Update center of mass and other properties such as friction.
  physicsBody->updateMassPropertiesFromColliders();
  physicState->addCollider(collider);
  physicState->init();

  return physicState;
}