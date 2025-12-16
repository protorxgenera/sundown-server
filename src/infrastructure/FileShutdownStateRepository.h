#pragma once
#include "../domain/IShutdownStateRepository.h"



class FileShutdownStateRepository : public IShutdownStateRepository
{
    public:
        FileShutdownStateRepository();

        void save(const ShutdownState &state) override;
        void clear() override;
        std::optional<ShutdownState> load() const override;

    private:
        QString stateFilePath() const;
};
