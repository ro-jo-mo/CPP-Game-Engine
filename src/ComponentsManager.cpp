#include "ecs/ComponentsManager.h"
#include "ecs/ComponentArray.h"
#include "ecs/Types.h"

void
ComponentsManager::DestroyEntity(Entity entity)
{
  for (const auto& [_, componentArrayPtr] : componentArrays) {
    componentArrayPtr->DestroyEntity(entity);
  }
}