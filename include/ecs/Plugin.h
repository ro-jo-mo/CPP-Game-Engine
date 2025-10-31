#pragma once

#include "ResourceManager.h"
#include "Scheduler.h"

namespace Cel {
    class Plugin {
        virtual void Build(Scheduler scheduler, ResourceManager &resourceManager) = 0;
    };
}
