#pragma once

#include "NodeVisitor.h"
#include "Transform.h"

/**
 * @brief Class which sole prupose is to
 *        traverse a subtree of the scene
 *        graph and initalize all geometrys.
 * 
 */
class InitVisitor : public NodeVisitor 
{
public:
  /**
   * @brief Construct a new Init Visitor object
   * 
   * @param program 
   */
  InitVisitor(GLuint program);
  ~InitVisitor();
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
private:
  GLuint m_program;
};