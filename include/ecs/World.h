#pragma once

#include "ComponentsManager.h"
#include "EntityManager.h"
#include "Types.h"
#include <vector>

class World
{
public:
  template<typename... Components>
  Entity Spawn(Components... components);
  void Destroy(Entity entity);
  template<typename Component>
  void AddComponent(Entity entity, Component component);
  template<typename Component>
  void RemoveComponent(Entity entity);
  bool Flush();

private:
  class Command
  {
  public:
    virtual void Execute() = 0;
  };
  template<typename T>
  class AddCommand : public Command
  {
  public:
    template<typename T>
    AddCommand(Entity ent, T comp, World& wld)
      : entity(ent)
      , component(comp)
      , world(wld){};

    void Execute() override;

  private:
    Entity entity;
    T component;
    World& world;
  };

  template<typename T>
  class RemoveCommand : public Command
  {
  public:
    template<typename T>
    RemoveCommand(Entity ent, World& wld)
      : entity(ent)
      , world(wld){};

    void Execute() override;

  private:
    Entity entity;
    World& world;
  };

  ComponentsManager& componentsManager;
  EntityManager& entityManager;
  std::vector<std::unique_ptr<Command>> toAdd;
  std::vector<std::unique_ptr<Command>> toRemove;
  std::vector<Entity> toDestroy;
};

template<typename... Components>
inline Entity
World::Spawn(Components... components)
{
  auto id = entityManager.AllocateEntity();
  ((void)AddComponent(id, components), ...);
  return id;
}

template<typename Component>
inline void
World::AddComponent(Entity entity, Component component)
{
  toAdd.push_back(
    std::make_unique(AddCommand<Component>(entity, component, *this)));
}

template<typename Component>
inline void
World::RemoveComponent(Entity entity)
{
  toRemove.push_back(std::make_unique(RemoveCommand<Component>(entity, *this)));
}

template<typename T>
inline void
World::AddCommand<T>::Execute()
{
  world.componentsManager.AddComponent(entity, component);
}

template<typename T>
inline void
World::RemoveCommand<T>::Execute()
{
  world.componentsManager.RemoveComponent(entity);
}
