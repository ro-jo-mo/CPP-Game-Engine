#pragma once
#include "Ecs.h"

class Plugin {
    virtual void Build(Ecs &ecs) = 0;
};
