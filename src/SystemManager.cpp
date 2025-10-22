#include "ecs/SystemManager.h"

void
SystemManager::UpdateViews()
{
  for (auto& view : views) {
    view->UpdateView();
  }
}
