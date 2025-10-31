#pragma once

#include "System.h"
#include "SystemManager.h"
#include "Types.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Cel {
  class ScheduleGraph {
  public:
    explicit ScheduleGraph(SystemManager &systemManager)
      : manager(systemManager) {
    };

    template<typename T>
    void AddNode();

    template<typename From, typename To>
    void AddEdge();

    void Execute();

  private:
    void ExecuteSystem(std::type_index id,
                       std::unordered_set<std::type_index> &executed);

    bool CheckRequirements(std::type_index id,
                           std::unordered_set<std::type_index> &executed);

    void RecursivelyExecute(std::type_index id,
                            std::unordered_set<std::type_index> &executed);

    std::unordered_map<std::type_index, std::unordered_set<std::type_index> >
    adjacencyList{};
    std::unordered_map<std::type_index, std::unordered_set<std::type_index> >
    requirements{};
    std::unordered_map<std::type_index, std::unique_ptr<System> > idToSystem{};
    SystemManager &manager;
  };

  template<typename T>
  void
  ScheduleGraph::AddNode() {
    static_assert(std::is_base_of_v<System, T>, "Must be a system type");

    idToSystem[typeid(T)] = T::Create;
  }

  template<typename From, typename To>
  void
  ScheduleGraph::AddEdge() {
    adjacencyList[typeid(From)].insert(typeid(To));
    requirements[typeid(To)].insert(typeid(From));
  }
}
