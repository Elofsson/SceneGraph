#pragma once

#include <vector>
#include <memory>

class Group;
class Transform;
class Geometry;
class Node;

class UpdateCallback
{
public:
  virtual void update() = 0;
};

typedef std::vector<std::shared_ptr<UpdateCallback>> CallbackVector;