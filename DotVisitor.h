#pragma once

#include "NodeVisitor.h"
#include <string>
#include <stack>
#include <fstream>
#include <iostream>

class DotVisitor : public NodeVisitor
{
public:
  DotVisitor(std::string fileName);
  DotVisitor(GLuint program);
  virtual ~DotVisitor() override;
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
  void close();
private:
  std::stack<std::string> m_dotstack;
  std::ofstream m_dotfile;
  int m_tranformCounter;
  int m_groupCounter;
  int m_geometryCounter;
};
