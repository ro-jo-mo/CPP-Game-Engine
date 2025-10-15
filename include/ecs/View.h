#include "ComponentArray.h"
#include "ComponentsManager.h"
#include "Types.h"
#include <memory>

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
  View(ComponentsManager manager);

private:
  static constexpr std::size_t totalTypes =
    sizeof...(Include) + sizeof...(Exclude);
  std::array<std::shared_ptr<IComponentArray>, totalTypes> componentArrays;
};

template<typename... Include, typename... Exclude>
inline View<IncludedComponentList<Include...>,
            ExcludedComponentList<Exclude...>>::View(ComponentsManager manager)
{
}

class Example
{
private:
  std::array<float, 5> exampleArray;
};