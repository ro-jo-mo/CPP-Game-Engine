#include "System.h"
#include "Types.h"
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ScheduleGraph
{
public:
  template<typename T>
  void AddNode();
  template<typename From, typename To>
  void AddEdge();
  void Execute();

private:
  std::unordered_map<std::type_index, std::vector<std::type_index>>
    adjacencyList;
  std::unordered_set<std::type_index> entryPoints;
  std::unordered_map<std::type_index, System> idToSystem;
};

template<typename T>
inline void
ScheduleGraph::AddNode()
{
  static_assert(std::is_base_of<System, T>::value, "Must be a system type");

  auto id = typeid(T);
  entryPoints.insert(id);
  adjacencyList[id];
  idToSystem[id] = T();
}

template<typename From, typename To>
inline void
ScheduleGraph::AddEdge()
{
  entryPoints.erase(typeid(To));
  adjacencyList.at(typeid(From)).push_back(typeid(To));
}
