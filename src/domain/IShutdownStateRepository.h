#pragma once

#include "ShutdownState.h"
#include <optional>

class IShutdownStateRepository
{
    public:
        virtual ~IShutdownStateRepository() = default;

        virtual void save(const ShutdownState& state) = 0;
        virtual void clear() = 0;

        virtual std::optional<ShutdownState> load() const = 0;

};
