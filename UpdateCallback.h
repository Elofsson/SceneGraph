#pragma once

#include <vector>
#include <memory>

class Group;
class Transform;
class Geometry;
class Node;


template<typename T>

class UpdateCallback
{
public:
  UpdateCallback(bool callOnce) { m_callonce = callOnce; }
  bool callOnce() { return m_callonce; }
  virtual bool update(T &g) = 0;

private:
  bool m_callonce;
};

typedef std::vector<std::shared_ptr<UpdateCallback<Node>>> CallbackVector;