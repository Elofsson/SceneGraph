#pragma once

#include <vector>
#include <memory>

class UpdateCallback
{
public:
  virtual void update() = 0;
};

typedef std::vector<std::shared_ptr<UpdateCallback>> CallbackVector;