#pragma once

#include "SystemManager.h"
#include <memory>

class System
{
public:
  System(SystemManager manager) {};
  virtual void Execute() = 0;
};
