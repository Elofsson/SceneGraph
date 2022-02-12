#include "RenderVisitor.h"

using namespace std;

//FIXME see where this should be done.
/* Apply object's transformation matrix */
//glm::mat4 obj2World = modelMatrix * this->object2world;
//glUniformMatrix4fv(m_uniform_m, 1, GL_FALSE, glm::value_ptr(obj2World));

/* Transform normal vectors with transpose of inverse of upper left
3x3 model matrix (ex-gl_NormalMatrix): */
//glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(obj2World)));
//glUniformMatrix3fv(m_uniform_m_3x3_inv_transp, 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));

RenderVisitor::RenderVisitor(GLuint program) : NodeVisitor(program)
{
	std::shared_ptr<State> defaultState = std::shared_ptr<State>(new State());
	m_states.push(defaultState);
	//TODO consider calling this in a init method for better error checking.
	//Get the location for model matrix.
	const char* uniform_name;
	uniform_name = "m";
	m_uniform_m = glGetUniformLocation(program, uniform_name);
	if (m_uniform_m == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}

	//Get the location for normal matrix.
	uniform_name = "m_3x3_inv_transp";
	m_uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
	if (m_uniform_m_3x3_inv_transp == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
	}
}

void RenderVisitor::visit(Group &g)
{ 

	bool pushedState = false;
	if(!g.emptyState())
	{
		pushedState = true;
		mergeAndPushState(g.getState());
	}

	NodeVisitor::visit(g);

	if(pushedState)
	{
		m_states.pop();
	}
}

void RenderVisitor::visit(Transform &t)
{
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
	NodeVisitor::visit(t);

  //Pop stack.
	m_transform_matrices.pop();

	if(pushedState)
	{
		m_states.pop();
	}
}


void RenderVisitor::visit(Geometry &g)
{
	
	//Set uniforms here maybe?
	if(m_transform_matrices.empty())
	{
		//cout << "Empty transform stack" << endl;
		return;
	}

	//TODO Make apply method for geometry.
	//Get model matrix.
	glm::mat4 object2world =  m_transform_matrices.top();
	glUniformMatrix4fv(m_uniform_m, 1, GL_FALSE, glm::value_ptr(object2world));

	/* Transform normal vectors with transpose of inverse of upper left
	3x3 model matrix (ex-gl_NormalMatrix): */
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(object2world)));
	glUniformMatrix3fv(m_uniform_m_3x3_inv_transp, 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));


	std::shared_ptr<State> geometryState = m_states.top();
	geometryState->merge(g.getState()); 
	geometryState->apply();

	g.draw();

	geometryState->unbindTextures();
}

void RenderVisitor::mergeAndPushState(std::shared_ptr<State> inputState)
{
	std::shared_ptr<State> newState = std::shared_ptr<State>(new State(m_states.top()));
	newState->merge(inputState);
	m_states.push(newState);
}