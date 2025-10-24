#pragma once

#include "ComponentsManager.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "SystemManager.h"
#include <concepts>
#include "Plugin.h"
#include "ScheduleGraph.h"
#include "Time.h"
#include "World.h"
#include "Schedule.h"


class Ecs {
  // Create all managers
  // Register time, world resources
  // Create schedules
  // Update time
  // Add plugins
public:
  Ecs() : systemManager(componentsManager) {
    resourceManager.InsertResource(std::make_shared<Time>(1.0f / 60.0f));
    resourceManager.InsertResource(std::make_shared<World>(componentsManager, entityManager));
  }

  void Run();

  template<typename T>
    requires std::derived_from<T, Plugin>
  Ecs &AddPlugin();

private:
  ComponentsManager componentsManager{};
  EntityManager entityManager{};
  ResourceManager resourceManager{};
  SystemManager systemManager;

  std::array<ScheduleGraph, Schedule::ScheduleSize> schedules();
};

template<typename T> requires std::derived_from<T, Plugin>
Ecs &Ecs::AddPlugin() {
  T().Build(this);
}


