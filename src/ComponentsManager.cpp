#include "ecs/ComponentsManager.h"

#include <ranges>

#include "ecs/ComponentArray.h"
#include "ecs/Types.h"

void
ComponentsManager::DestroyEntity(Entity entity) {
  for (const auto &componentArrayPtr: componentArrays | std::views::values) {
    componentArrayPtr->DestroyEntity(entity);
  }
}
