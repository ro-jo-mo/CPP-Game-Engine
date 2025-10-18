#include "ComponentArray.h"
#include "ComponentsManager.h"
#include "Types.h"
#include <algorithm>
#include <memory>
#include <tuple>
#include <unordered_set>

template<typename T>
struct TypeStorage
{};

template<typename... T>
struct TypeList
{};

template<typename... T>
struct IncludedComponentList : TypeList<T>
{};

template<typename... T>
struct ExcludedComponentList : TypeList<T>
{};

template<typename, typename>
class View;

template<typename... Include, typename... Exclude>
class View<IncludedComponentList<Include...>, ExcludedComponentList<Exclude...>>
{
public:
  View(std::shared_ptr<ComponentsManager> manager);

private:
  std::tuple<std::shared_ptr<ComponentArray<Include>>...>
    includedComponentArrays;
};

template<typename... Include, typename... Exclude>
inline View<IncludedComponentList<Include...>,
            ExcludedComponentList<Exclude...>>::
  View(std::shared_ptr<ComponentsManager> manager)
{
  includedComponentArrays =
    std::make_tuple(manager->GetComponentArray<Include>()...);

  auto getEntityLists = [](auto&& componentArrays) {
    return std::array{ componentArrays->GetEntityList() };
  };

  auto entityArrays = std::apply(getEntityLists, includedComponentArrays);

  // find smallest array, use it as the base
  size_t smallestIndex = 0;
  size_t smallestSize = 9999;

  for (int i = 0; i < entityArrays.size(); ++i) {
    if (entityArrays[i].size() < smallestSize) {
      smallestSize = entityArrays[i].size();
      smallestIndex = i;
    }
  }
  // put smallest list at the front
  std::swap(entityArrays[0], entityArrays[smallestIndex]);

  std::unordered_set<Entity> included;

  for (auto& [entity, _] : entityArrays[0]) {
    auto inSet = std::all_of(
      entityArrays.begin() + 1, entityArrays.end(), [](const auto& map) {
        return map.find(entity) != map.end();
      });

    if (inSet) {
      included.insert(entity);
    }
  }

  // for each excluded list, does entity exist inside
  // if so, remove
  auto excludedEntityArrays =
    std::invoke(getEntityLists, manager->GetComponentArray<Exclude>()...);

  for (auto& entity : included) {
    auto inSet = std::all_of(
      entityArrays.begin() + 1, entityArrays.end(), [](const auto& map) {
        return map.find(entity) != map.end();
      });

    if (inSet) {
      included.insert(entity);
    }
  }
}
