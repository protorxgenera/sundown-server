#include "ShutdownScheduler.h"

ShutdownScheduler::ShutdownScheduler(IShutdownStateRepository &repository) : m_repository(repository)
{
    loadInitialState();
}

void ShutdownScheduler::loadInitialState()
{
    auto loaded = m_repository.load();
    if (loaded.has_value())
    {
        m_state = *loaded;
    } else
    {
        m_state = ShutdownState::inactive();
    }

    qDebug() << "ShutdownScheduler: initial state loaded";
}


bool ShutdownScheduler::scheduleAt(const QDateTime &time, ShutdownOrigin origin)
{
    qDebug() << "ShutdownScheduler: scheduleAt() hit";

    if (!time.isValid() || time <= QDateTime::currentDateTime())
    {
        return false;
    }
    m_state = ShutdownState::activeAt(time, origin);

    qDebug() << "ShutdownScheduler: inside scheduleAt() right outside repo.save()";
    m_repository.save(m_state);
    return true;
}

void ShutdownScheduler::cancel()
{
    m_state = ShutdownState::inactive();
    m_repository.clear();
}

bool ShutdownScheduler::hasActiveShutdown() const
{
    return m_state.active;
}

ShutdownState ShutdownScheduler::currentState() const
{
    return m_state;
}
