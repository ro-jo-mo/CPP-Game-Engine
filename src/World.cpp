#include "ecs/World.h"

void
World::Destroy(Entity entity)
{
  entityManager.DestroyEntity(entity);
  componentsManager.DestroyEntity(entity);
}

bool
World::Flush()
{
  // order
  // add
  // remove
  // destroy
  for (auto& cmd : toAdd) {
    cmd->Execute();
  }
  for (auto& cmd : toRemove) {
    cmd->Execute();
  }
  for (auto& ent : toDestroy) {
    entityManager.DestroyEntity(ent);
    componentsManager.DestroyEntity(ent);
  }
  auto changesMade = toAdd.size() + toRemove.size() + toDestroy.size() > 0;
  toAdd.clear();
  toRemove.clear();
  toDestroy.clear();
  return changesMade;
}