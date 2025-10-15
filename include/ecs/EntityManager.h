#pragma once
#include "Types.h"
#include <vector>
#include <array>
#include <queue>

// Allocates entity ids
// To do this, it needs to manage a pool of used ids and deleted ids

class EntityManager {
public:
	Entity AllocateEntity();
	void DestroyEntity(Entity entity);
private:
	std::queue<Entity> toReuse;
	std::array<Signature, MAX_ENTITIES> signatures{};
	Entity entityCounter;
};