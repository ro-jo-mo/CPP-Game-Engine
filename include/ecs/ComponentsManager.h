#pragma once
#include "ComponentArray.h"
#include "Types.h"
#include <array>
#include <memory>
#include <typeindex>
#include <unordered_map>

class ComponentsManager
{
public:
  template<typename T>
  void RegisterComponent();
  template<typename T>
  T& GetComponent(Entity entity);
  template<typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentArray();
  void DeleteEntity(Entity entity);

private:
  std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>>
    componentArrays;
  std::array<std::type_index, MAX_COMPONENTS> signatureIndexToComponent;
  std::unordered_map<std::type_index, size_t> componentToSignatureIndex;
};

template<typename T>
inline void
ComponentsManager::RegisterComponent()
{
  if (componentArrays.find(typeid(T)) != componentArrays.end()) {
    return;
  }
  signatureIndexToComponent[componentArrays.size()] = typeid(T);
  componentToSignatureIndex[typeid(T)] = componentArrays.size();
  componentArrays[typeid(T)] = std::make_shared<ComponentArray<T>>();
}

template<typename T>
inline std::shared_ptr<ComponentArray<T>>
ComponentsManager::GetComponentArray()
{
  RegisterComponent<T>();
  return std::static_pointer_cast<ComponentArray<T>>(
    componentArrays[typeid(T)]);
}