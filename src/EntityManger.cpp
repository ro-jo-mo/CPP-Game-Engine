#include "ecs/EntityManager.h"

Entity EntityManager::AllocateEntity()
{
	if (toReuse.empty()) {
		return entityCounter++;
	}
	auto entity = toReuse.front();
	toReuse.pop();
	return entity;
}

void EntityManager::DestroyEntity(Entity entity)
{
	signatures[entity] = Signature(0);
	toReuse.push(entity);
}