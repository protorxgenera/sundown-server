#pragma once
#include "../ports/IShutdownStateRepository.h"

class InMemoryShutdownStateRepository : public IShutdownStateRepository
{
    public:
        void save(const ShutdownState &state) override
        {
            m_state = state;
        }

        void clear() override
        {
            m_state.reset();
        };

        std::optional<ShutdownState> load() const override
        {
            return m_state;
        };

    private:
        std::optional<ShutdownState> m_state;

};

