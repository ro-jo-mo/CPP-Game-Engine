#pragma once

#include <cstdint>
#include <bitset>

namespace Cel {
    using Entity = std::uint32_t;
    constexpr Entity MAX_ENTITIES = 2048;

    using ComponentType = std::uint8_t;
    constexpr ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}
