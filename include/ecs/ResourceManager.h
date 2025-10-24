#pragma once

#include "Resource.h"
#include "Types.h"
#include <memory>
#include <tuple>
#include <typeindex>
#include <unordered_map>

class ResourceManager {
public:
  template<typename T>
  void InsertResource();

  template<typename T>
  void InsertResource(std::shared_ptr<T> resource);

  template<typename... Resources>
  std::tuple<std::shared_ptr<Resources>...> GetResources();

private:
  std::unordered_map<std::type_index, std::shared_ptr<Resource> > resources;
};

template<typename T>
inline void
ResourceManager::InsertResource() {
  InsertResource(std::make_shared<T>());
}

template<typename T>
inline void
ResourceManager::InsertResource(std::shared_ptr<T> resource) {
  resources[typeid(T)] = resource;
}

template<typename... Resources>
inline std::tuple<std::shared_ptr<Resources>...>
ResourceManager::GetResources() {
  return std::make_tuple(
    std::static_pointer_cast<Resources>(resources[typeid(Resources)])...);
}
