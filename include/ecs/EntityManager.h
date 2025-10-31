#pragma once

#include "Types.h"
#include <array>
#include <queue>

namespace Cel {
  class EntityManager {
  public:
    Entity AllocateEntity();

    void DestroyEntity(Entity entity);

  private:
    std::queue<Entity> toReuse;
    Entity entityCounter;
  };
}
