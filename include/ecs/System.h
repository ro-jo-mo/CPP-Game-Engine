#include "Ecs.h"
#include "Types.h"
#include <typeindex>
#include <vector>

class System
{
public:
  System(Ecs ecs);
  virtual void ExecuteSystem() = 0;
};
