#pragma once
#include "Types.h"
#include <unordered_map>
#include <array>
#include "ComponentsManager.h"

class IComponentArray {
public: 
	virtual void DeleteEntity(Entity entity) = 0;
};


template <typename T>
class ComponentArray : public IComponentArray {
public:
	void DeleteEntity(Entity entity) override {
		if (entityToComponent.find(entity) != entityToComponent.end()) {
			RemoveComponent(entity);
		}
	}
	void AddComponent(T component,Entity entity);
	void RemoveComponent(Entity entity);
	T& GetComponent(Entity entity);
private:
	std::array<T, MAX_ENTITIES> components;
	std::unordered_map<Entity, size_t> entityToComponent;
	std::unordered_map<size_t, Entity> componentToEntity;
	Entity totalComponents;
};



template<typename T>
inline void ComponentArray<T>::AddComponent(T component, Entity entity)
{
	components[totalComponents] = component;
	entityToComponent[entity] = totalComponents;
	componentToEntity[totalComponents] = entity;
	totalComponents++;
}

template<typename T>
inline void ComponentArray<T>::RemoveComponent(Entity entity)
{
	auto index = entityToComponent[entity];
	
	auto last = --totalComponents;
	components[index] = components[last];

	componentToEntity.erase(index);
	entityToComponent.erase(entity);
	
}

template<typename T>
inline T& ComponentArray<T>::GetComponent(Entity entity)
{
	auto index = entityToComponent[entity];
	return components[index];
}
