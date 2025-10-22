#pragma once

#include "ComponentArray.h"
#include "ComponentsManager.h"
#include "Types.h"
#include <algorithm>
#include <iterator>
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

class IView
{
public:
  void UpdateView();
};

template<typename, typename>
class View;

template<typename... Include, typename... Exclude>
class View<IncludedComponentList<Include...>, ExcludedComponentList<Exclude...>>
  : public IView
{
public:
  View(std::shared_ptr<ComponentsManager> componentsManager);
  void UpdateView() override;
  std::tuple<Include&...> Get(Entity entity);

  class Iterator
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    Iterator(Iter currentIter,
             Iter endIter,
             View<IncludedComponentList<Include...>,
                  ExcludedComponentList<Exclude...>>& viewRef)
      : current(currentIter)
      , end(endIter)
      , view(viewRef) {};

    bool operator!=(const Iterator& other) const
    {
      return current != other.current;
    }

    void operator++() { ++current; }

    std::tuple<Include&...> operator*()
    {
      Entity entity = *current;
      return view.Get(entity);
    }

  private:
    using Iter = std::unordered_set::iterator;
    Iter current;
    Iter end;
    View<IncludedComponentList<Include...>, ExcludedComponentList<Exclude...>>&
      view;
  };
  Iterator begin() { return Iterator(included.begin(), included.end(), &this); }
  Iterator end() { return Iterator(included.end(), included.end(), &this); }

private:
  std::tuple<std::shared_ptr<ComponentArray<Include>>...>
    includedComponentArrays;
  std::shared_ptr<ComponentsManager> manager;
  std::unordered_set<Entity> included;
};

template<typename... Include, typename... Exclude>
inline View<IncludedComponentList<Include...>,
            ExcludedComponentList<Exclude...>>::
  View(std::shared_ptr<ComponentsManager> componentsManager)
  : manager(componentsManager)
{
  includedComponentArrays =
    std::make_tuple(manager->GetComponentArray<Include>()...);
  UpdateView();
}

template<typename... Include, typename... Exclude>
inline void
View<IncludedComponentList<Include...>,
     ExcludedComponentList<Exclude...>>::UpdateView()
{
  auto getEntityLists = [](auto&& componentArrays) {
    return std::array{ componentArrays->GetEntityList() };
  };

  auto entityArrays = std::apply(getEntityLists, includedComponentArrays);

  // find smallest array, use it as the base
  size_t smallestIndex = 0;
  size_t smallestSize = 9999;

  auto entityInSet =
    [](const auto& map) { return map.find(entity) != map.end(); }

  for (int i = 0; i < entityArrays.size(); ++i)
  {
    if (entityArrays[i].size() < smallestSize) {
      smallestSize = entityArrays[i].size();
      smallestIndex = i;
    }
  }
  // put smallest list at the front
  std::swap(entityArrays[0], entityArrays[smallestIndex]);

  included.clear();

  for (auto& [entity, _] : entityArrays[0]) {
    auto inSet =
      std::all_of(entityArrays.begin() + 1, entityArrays.end(), entityInSet);

    if (inSet) {
      included.insert(entity);
    }
  }

  // for each excluded list, does entity exist inside
  // if so, remove
  auto excludedEntityArrays =
    std::invoke(getEntityLists, manager->GetComponentArray<Exclude>()...);

  for (auto& entity : included) {
    auto inSet = std::any_of(
      excludedEntityArrays.begin(), excludedEntityArrays.end(), entityInSet);

    if (inSet) {
      included.erase(entity);
    }
  }
}

template<typename... Include, typename... Exclude>
inline std::tuple<Include&...>
View<IncludedComponentList<Include...>, ExcludedComponentList<Exclude...>>::Get(
  Entity entity)
{
  return std::make_tuple(std::get<Include>(arrays)->GetComponent(entity)...)
}
