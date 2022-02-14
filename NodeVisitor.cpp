#include "NodeVisitor.h"
#include "Transform.h"

using namespace std;

NodeVisitor::NodeVisitor()
{
}

NodeVisitor::~NodeVisitor()
{
}

//TODO make one method for this.
void NodeVisitor::traverse(Group &g)
{
  //std::cout << "Nr of children for " << g.name << " is: " << g.getChildren().size() << std::endl;
  NodeVector children = g.getChildren();
  int debug = 0;
  for(auto child : children)
  {
    //std::cout << "Looping for  " << g.name << " : "<< debug << std::endl;
    debug++;
    child->accept(*this);
  }
}

void NodeVisitor::traverse(Transform &g)
{
  //std::cout << "Nr of children for " << g.name << " is: " << g.getChildren().size() << std::endl;
  NodeVector children = g.getChildren();
  int debug = 0;
  for(auto child : children)
  {
    //std::cout << "Looping for  " << g.name << " : "<< debug << std::endl;
    debug++;
    child->accept(*this);
  }
}
