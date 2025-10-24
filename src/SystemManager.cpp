#include "ecs/SystemManager.h"

void
SystemManager::UpdateViews() const {
  for (const auto &view: views) {
    view->UpdateView();
  }
}
