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
  UpdateCallback(bool callOnce) { m_callonce = callOnce; }
  bool callOnce() { return m_callonce; }
  virtual bool update(Group &g) { return false; }
  virtual bool update(Geometry &g) { return false; }
  virtual bool update(Transform &t) { return false; }

private:
  bool m_callonce;
};

typedef std::vector<std::shared_ptr<UpdateCallback>> CallbackVector;