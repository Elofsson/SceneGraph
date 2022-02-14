#pragma once

#include "NodeVisitor.h"
#include <string>
#include <stack>
#include <fstream>
#include <iostream>

/**
 * @brief Visitor whose purpose is to create a dotfile
 *        in order to visualise the scenegraph and easier
 *        debug. In order for the file to be saved
 *        close has to be called when finished.
 * 
 */
class DotVisitor : public NodeVisitor
{
public:
  /**
   * @brief Construct a new Dot Visitor object
   *        which will create a new dotfile with
   *        the provided filename.
   * 
   * @param fileName Name of the dotfile.
   */
  DotVisitor(std::string fileName);
  virtual ~DotVisitor() override;
  virtual void visit(Group &g) override;
  virtual void visit(Transform &t) override;
  virtual void visit(Geometry &g) override;
  void close();
private:
  std::stack<std::string> m_dotstack;
  std::ofstream m_dotfile;

  //Used for naming.
  int m_tranformCounter;
  int m_groupCounter;
  int m_geometryCounter;
};
