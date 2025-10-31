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
#include "Scheduler.h"

namespace Cel {
  class Ecs {
    // Create all managers
    // Register time, world resources
    // Create schedules
    // Update time
    // Add plugins
  public:
    Ecs() : componentsManager(), systemManager(componentsManager) {
      resourceManager.InsertResource(std::make_shared<Time>(1.0f / 60.0f));
      resourceManager.InsertResource(std::make_shared<World>(componentsManager, entityManager));
      for (std::size_t i; i < Schedule::ScheduleSize; ++i) {
        schedules.push_back(ScheduleGraph(systemManager));
      }
    }

    void Run();

    template<typename T>
      requires std::derived_from<T, Plugin>
    Ecs &AddPlugin();

  private:
    ComponentsManager componentsManager;
    EntityManager entityManager;
    ResourceManager resourceManager;
    SystemManager systemManager;

    std::vector<ScheduleGraph> schedules;
  };

  template<typename T> requires std::derived_from<T, Plugin>
  Ecs &Ecs::AddPlugin() {
    T().Build(Scheduler(schedules), resourceManager);
  }
}
