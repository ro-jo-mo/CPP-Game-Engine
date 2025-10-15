#include "ComponentsManager.h"
#include "System.h"
#include "View.h"
#include <array>
#include <memory>

class SystemManager
{
public:
  SystemManager(std::shared_ptr<ComponentsManager> manager)
    : componentsManager(manager)
  {
  }

  template<typename FirstComponent,
           typename... OtherComponents,
           typename... ExcludedComponents>
  View<IncludedComponentList<TypeStorage<FirstComponent>,
                             TypeStorage<OtherComponents...>>,
       ExcludedComponentList<TypeStorage<ExcludedComponents...>>>
  CreateView(ExcludedComponentList<ExcludedComponents...> excluded =
               ExcludedComponentList{});

private:
  std::shared_ptr<ComponentsManager> componentsManager;
};

template<typename FirstComponent,
         typename... OtherComponents,
         typename... ExcludedComponents>
inline View<IncludedComponentList<TypeStorage<FirstComponent>,
                                  TypeStorage<OtherComponents...>>,
            ExcludedComponentList<TypeStorage<ExcludedComponents...>>>
SystemManager::CreateView(ExcludedComponentList<ExcludedComponents...> excluded)
{
  // Need to find all component arrays, and then find the common entities
  View<IncludedComponentList<TypeStorage<FirstComponent>,
                             TypeStorage<OtherComponents...>>,
       ExcludedComponentList<TypeStorage<ExcludedComponents...>>>
  view();
}
