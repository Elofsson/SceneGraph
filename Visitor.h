#pragma once

#include "Group.h"

class Visitor 
{

public:
  virtual void visit(Group *group) = 0;
};