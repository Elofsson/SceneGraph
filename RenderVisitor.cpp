#include "RenderVisitor.h"

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