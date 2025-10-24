#pragma once

#include "ComponentsManager.h"
#include "View.h"
#include <array>
#include <memory>

class SystemManager {
public:
  SystemManager(const ComponentsManager &manager)
    : componentsManager(manager) {
  }

  template<typename FirstComponent,
    typename... OtherComponents,
    typename... ExcludedComponents>
  std::shared_ptr<
    View<IncludedComponentList<FirstComponent, OtherComponents...>,
      ExcludedComponentList<ExcludedComponents...> > >
  CreateView(ExcludedComponentList<ExcludedComponents...> excluded =
      ExcludedComponentList{});

  void UpdateViews() const;

private:
  ComponentsManager componentsManager;
  std::vector<std::shared_ptr<IView> > views;
};

template<typename FirstComponent,
  typename... OtherComponents,
  typename... ExcludedComponents>
inline std::shared_ptr<
  View<IncludedComponentList<FirstComponent, OtherComponents...>,
    ExcludedComponentList<ExcludedComponents...> > >
SystemManager::CreateView(ExcludedComponentList<ExcludedComponents...> excluded) {
  auto view = std::make_shared<View<IncludedComponentList<FirstComponent, OtherComponents...>,
    ExcludedComponentList<ExcludedComponents...> > >(this);
  views.push_back(view);
  return view;
}
