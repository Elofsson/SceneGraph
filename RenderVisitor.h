#pragma once

#include "NodeVisitor.h"
#include "Geometry.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Debug.h"
#include "State.h"
//TODO Node visitor to handle rendering.
//TODO Apply transformations, states, geometry when encountrered in scenegraph.
//TODO Scenegraph should not be modified by this visitor.
//TODO When transformation matrix is visited, push and concatinate matrix to stack.
//TODO Each drawable object has its own model transform.
//TODO When leaving trasformation node, pop the matrix stack.


class RenderVisitor : public NodeVisitor
{
public:
  RenderVisitor();
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
  void forceProgram(bool enabled, GLuint program);

private:
  void mergeAndPushState(std::shared_ptr<State> inputState);
  void updatePhysics(Node &g);

  GLuint m_forceProgram;
  bool m_force;

  GLuint m_uniform_m_3x3_inv_transp;
  GLuint m_uniform_m;
  std::stack<glm::mat4> m_transform_matrices;
  std::stack<std::shared_ptr<State>> m_states;
  std::shared_ptr<PhysicsState> m_currentPhysics;
};