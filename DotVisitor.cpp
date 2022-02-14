#include "DotVisitor.h"

DotVisitor::DotVisitor(std::string fileName)
{
  m_dotfile.open(fileName);
  m_dotstack.push("Root");
  m_tranformCounter = 0;
  m_groupCounter = 0;
  m_geometryCounter = 0;
}

DotVisitor::~DotVisitor()
{
}

void DotVisitor::visit(Group &g)
{
  std::string thisGroup = "G_";
  thisGroup.append(std::to_string(m_groupCounter));
  m_groupCounter++;

  std::cout << thisGroup << std::endl;

  std::string previous = m_dotstack.top();
  m_dotstack.push(thisGroup);
  std::string groupDotStr = previous;
  groupDotStr.append(" -- ");
  groupDotStr.append(thisGroup);

  std::cout << "Group " << groupDotStr << std::endl;
  m_dotfile << groupDotStr << "[type=s]" << std::endl;

  NodeVisitor::traverse(g);

  m_dotstack.pop();
}

void DotVisitor::visit(Transform &t) 
{
  //Create transform name and push to stack.
  std::string thisTransform = "T_";
  thisTransform.append(std::to_string(m_tranformCounter));
  m_tranformCounter++;

  //Create dot connection to be written to file.
  std::string previous = m_dotstack.top();
  m_dotstack.push(thisTransform);
  std::string transformDotStr = previous;
  transformDotStr.append(" --");
  transformDotStr.append(thisTransform);
  
  std::cout << "Transform " << transformDotStr << std::endl;
  m_dotfile << transformDotStr << "[type=s]" << std::endl;

  NodeVisitor::traverse(t);

  m_dotstack.pop();
}

void DotVisitor::visit(Geometry &g) 
{
  std::string thisGeometry = "GE_";
  thisGeometry.append(std::to_string(m_geometryCounter));
  m_geometryCounter++;

  std::string previous = m_dotstack.top();
  std::string geometryDotStr = previous;
  geometryDotStr.append(" --");
  geometryDotStr.append(thisGeometry);
  std::cout << "Geometry " << geometryDotStr << std::endl;

  m_dotfile << geometryDotStr << "[type=s]" << std::endl;
}

void DotVisitor::close()
{
  m_dotfile.close();
}