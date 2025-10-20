#include "ComponentsManager.h"
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
  View<IncludedComponentList<FirstComponent, OtherComponents...>,
       ExcludedComponentList<ExcludedComponents...>>
  CreateView(ExcludedComponentList<ExcludedComponents...> excluded =
               ExcludedComponentList{});

private:
  std::shared_ptr<ComponentsManager> componentsManager;
};

template<typename FirstComponent,
         typename... OtherComponents,
         typename... ExcludedComponents>
inline View<IncludedComponentList<FirstComponent, OtherComponents...>,
            ExcludedComponentList<ExcludedComponents...>>
SystemManager::CreateView(ExcludedComponentList<ExcludedComponents...> excluded)
{
  return View<IncludedComponentList<FirstComponent, OtherComponents...>,
              ExcludedComponentList<ExcludedComponents...>>(this);
}
