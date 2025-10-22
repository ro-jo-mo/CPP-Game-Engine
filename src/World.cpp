#include "ecs/World.h"

void
World::Destroy(Entity entity)
{
  entityManager.DestroyEntity(entity);
  componentsManager.DestroyEntity(entity);
}

void
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
}