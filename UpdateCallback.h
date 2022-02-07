#pragma once

#include <vector>
#include <memory>

class Group;
class Transform;
class Geometry;

class UpdateCallback
{
public:
  virtual bool update(Group &g) = 0;
  virtual bool update(Transform &t) = 0;
  virtual bool update(Geometry &g) = 0;
};

typedef std::vector<std::shared_ptr<UpdateCallback>> CallbackVector;