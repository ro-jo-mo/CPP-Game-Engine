#include "ecs/SystemManager.h"

using namespace Cel;

void
SystemManager::UpdateViews() const {
  for (const auto &view: views) {
    view->UpdateView();
  }
}
