#pragma once

#include "System.h"
#include "SystemManager.h"
#include "Types.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ScheduleGraph
{
public:
  ScheduleGraph(auto systemManager)
    : manager(systemManager) {};
  template<typename T>
  void AddNode();
  template<typename From, typename To>
  void AddEdge();
  void Execute();

private:
  void ExecuteSystem(std::type_index id,
                     std::unordered_set<std::type_index>& executed);
  bool CheckRequirements(std::type_index id,
                         std::unordered_set<std::type_index>& executed);
  void RecursivelyExecute(std::type_index id,
                          std::unordered_set<std::type_index>& executed);

  std::unordered_map<std::type_index, std::unordered_set<std::type_index>>
    adjacencyList;
  std::unordered_map<std::type_index, std::unordered_set<std::type_index>>
    requirements;
  std::unordered_map<std::type_index, std::unique_ptr<System>> idToSystem;
  std::shared_ptr<SystemManager> manager;
};

template<typename T>
inline void
ScheduleGraph::AddNode()
{
  static_assert(std::is_base_of<System, T>::value, "Must be a system type");

  auto id = typeid(T);
  idToSystem[id] = T::Create;
}

template<typename From, typename To>
inline void
ScheduleGraph::AddEdge()
{
  adjacencyList[typeid(From)].insert(typeid(To));
  requirements[typeid(To)].insert(typeid(From));
}
