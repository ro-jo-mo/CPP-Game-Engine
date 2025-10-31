#pragma once

#include "SystemManager.h"
#include <memory>

namespace Cel {
  class System {
  public:
    explicit System(SystemManager &manager) {
    };

    virtual void Execute() = 0;
  };
}
