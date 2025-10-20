#include "ecs/ScheduleGraph.h"
#include <algorithm>
#include <cassert>
#include <typeindex>
#include <unordered_set>

void
ScheduleGraph::Execute()
{
  std::unordered_set<std::type_index> executed;

  for (auto& [id, requirement] : requirements) {
    if (requirement.empty()) {
      ExecuteSystem(id, executed);
    }
  }
  assert(executed.size() == adjacencyList.size() &&
         "Cycles found in dependencies, not all systems executed");
}

void
ScheduleGraph::ExecuteSystem(std::type_index id,
                             std::unordered_set<std::type_index>& executed)
{ // if this node has no requirements, we can start executing it
  idToSystem[id]->Execute();
  executed.insert(id);
  // additionally execute nodes that require this
  RecursivelyExecute(id, executed);
}

bool
ScheduleGraph::CheckRequirements(std::type_index id,
                                 std::unordered_set<std::type_index>& executed)
{
  return std::all_of(requirements[id].begin(),
                     requirements[id].end(),
                     [executed](auto& required) {
                       return executed.find(required) != executed.end();
                     });
}

void
ScheduleGraph::RecursivelyExecute(std::type_index parentId,
                                  std::unordered_set<std::type_index>& executed)
{
  for (auto& id : adjacencyList[parentId]) {
    if (CheckRequirements(id, executed)) {
      ExecuteSystem(id, executed);
      RecursivelyExecute(id, executed);
    }
  }
}
