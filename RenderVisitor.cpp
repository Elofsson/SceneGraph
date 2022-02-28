#include "RenderVisitor.h"

using namespace std;

RenderVisitor::RenderVisitor()
{
	std::shared_ptr<State> defaultState = std::shared_ptr<State>(new State());
	m_states.push(defaultState);
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
	g.initShaders(geometryState->getProgram());
	g.apply(object2world);

	//Render with furstate.
	std::cout << "Render with program: " << geometryState->getProgram() << std::endl;
	auto furState = geometryState->getFurState();
	if(furState != nullptr)
	{
		for(int layer = 0; layer < furState->getNumLayers(); layer++)
		{
			furState->apply(geometryState->getProgram(), layer);
			g.draw();
		}
	}

	//Render without furstate if it is not set.
	else
	{
		g.draw();
	}
}

void RenderVisitor::mergeAndPushState(std::shared_ptr<State> inputState)
{
	std::shared_ptr<State> newState = std::shared_ptr<State>(new State(m_states.top()));
	newState->merge(inputState);
	m_states.push(newState);
}