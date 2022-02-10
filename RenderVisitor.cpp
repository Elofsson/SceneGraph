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
	m_state = std::shared_ptr<State>(new State());

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
	//std::cout << "Mergeing state for: " << g.name << std::endl;
	if(!g.emptyState())
	{
		m_state->merge(g.getState());
	}
	NodeVisitor::visit(g);
}

void RenderVisitor::visit(Transform &t)
{
  //Push on stack.
	if(!t.emptyState())
	{
		m_state->merge(t.getState());
	}
  //Pop stack.
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

	//Apply state.
	if(!g.emptyState())
	{
		m_state->merge(g.getState());
	}


	if(g.name.find("monkey") != std::string::npos)
	{
		std::cout << "Monkey materials" << std::endl;
		Debug::printMaterial(g.getState()->getMaterial());
	}
	m_state->apply();

	g.draw();

	m_state->unbindTextures();

}