#include "RenderVisitor.h"
#include <glm/gtx/io.hpp>


using namespace std;

RenderVisitor::RenderVisitor()
{
	std::shared_ptr<State> defaultState = std::shared_ptr<State>(new State());
	m_states.push(defaultState);
	m_force = false;
	m_forceProgram = 0;
}

//Set renderToTexture
	//Apply.

void RenderVisitor::visit(Group &g)
{ 
	
	//std::cout << "Visit group" << std::endl;
	bool pushedState = false;
	if(!g.emptyState())
	{
		pushedState = true;
		mergeAndPushState(g.getState());
	}

  //updatePhysics(g);

	NodeVisitor::traverse(g);

	if(pushedState)
	{
		m_states.pop();
	}
}

void RenderVisitor::visit(Transform &t)
{
	//std::cout << "Visit transform" << std::endl;
	bool pushedState = false;
	if(!t.emptyState())
	{
		pushedState = true;
		mergeAndPushState(t.getState());
	}

  //Push on stack.
	if(m_transform_matrices.empty())
  {
    m_transform_matrices.push(t.object2world);
  }

  //calculate and concat matrix.
  else
  {
    glm::mat4 prevMat = m_transform_matrices.top();
    glm::mat4 newObject2world = prevMat * t.object2world;
    m_transform_matrices.push(newObject2world); 
  }

  	std::cout << "Visiting transform in rendervisitor: "<<  t.name << t.object2world << std::endl;
  //updatePhysics(t);

	
	//Traverse transforms children.
	NodeVisitor::traverse(t);

  //Pop stack.
	m_transform_matrices.pop();

	if(pushedState)
	{
		m_states.pop();
	}
}


void RenderVisitor::visit(Geometry &g)
{
	updatePhysics(g);

  if(m_transform_matrices.empty())
	{
		return;
	}

	std::shared_ptr<State> geometryState = m_states.top();
	if(!g.emptyState())
	{
		geometryState->merge(g.getState()); 
	}

	geometryState->apply();
	glm::mat4 object2world = m_transform_matrices.top();

	//std::cout << "Object2world in render visitor: " << object2world << std::endl;

  /*if(m_currentPhysics != nullptr)
  {
    reactphysics3d::RigidBody *body = m_currentPhysics->getBody();
    const reactphysics3d::Transform& transform = body->getTransform();
    const reactphysics3d::Matrix3x3 orientationMatrix = transform.getOrientation().getMatrix();
    const reactphysics3d::Vector3& position = transform.getPosition();
    std::cout << "Position " << position.x << " : " << position.y << " : " << position.z << std::endl;
	std::cout << "Object 2 world: [" << object2world[3][0] << ", " << object2world[3][1] << ", " << object2world[3][2] << " ]" << std::endl; 

	std::cout << "object2world BEFORE physics" << object2world << std::endl;


	float matrix[16]; 
    transform.getOpenGLMatrix(matrix);
	//glm::mat4 translation = glm::make_mat4(matrix);
	//object2world = translation * object2world;

	//float newPosx = object2world[3][0] + position.x;
	//float newPosy = object2world[3][1] + position.y;
	//float newPosz = object2world[3][2] + position.z;

    //glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(newPosx, newPosy, newPosz)); //glm::make_mat4(matrix);	
	//object2world = translation * object2world;


    //object2world = transformation * object2world;

	object2world[3][0] = position.x;
	object2world[3][1] = position.y;
	object2world[3][2] = position.z;
    
	std::cout << "object2world AFTER physics" << object2world << std::endl;
  }*/

	//Determine program to use. 
	GLuint programToUse;
	if(m_force)
	{
		programToUse = m_forceProgram;
	}

	else
	{
		programToUse = geometryState->getProgram(); 
	}

	g.initShaders(programToUse);
	g.apply(object2world);

	//Render with furstate if the state exists and if forcing has not been set.
	auto furState = geometryState->getFurState();
	if(furState != nullptr && !m_force)
	{
		furState->apply(g, programToUse);
	}

	//Render without furstate if it is not set.
	else
	{
		g.draw();
	}
}

void RenderVisitor::forceProgram(bool enabled, GLuint program)
{
	m_force = enabled;
	m_forceProgram = program;
}

void RenderVisitor::mergeAndPushState(std::shared_ptr<State> inputState)
{
	std::shared_ptr<State> newState = std::shared_ptr<State>(new State(m_states.top()));
	newState->merge(inputState);
	m_states.push(newState);
}

void RenderVisitor::updatePhysics(Node &g)
{
  if(g.getPhysics() != nullptr)
  {
    m_currentPhysics = g.getPhysics(); 
  }
}