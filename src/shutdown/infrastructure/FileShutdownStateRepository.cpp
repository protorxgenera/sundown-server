#include "FileShutdownStateRepository.h"

#include <qfile.h>
#include <qjsonobject.h>
#include <qsavefile.h>
#include <qstandardpaths.h>
#include <QDebug>
#include <qdir.h>
#include <qfileinfo.h>

FileShutdownStateRepository::FileShutdownStateRepository() = default;

QString FileShutdownStateRepository::stateFilePath() const
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString path = dir + "/shutdown_state.json";

    qDebug() << "State file path: " << path;

    return path;
}

void FileShutdownStateRepository::save(const ShutdownState &state)
{
    // create dir if it doesn't exist
    QString filePath = stateFilePath();
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();

    if (!dir.exists())
    {
        qDebug() << "Directory doesn't exist, creating: " << dir.absolutePath();
        if (!dir.mkpath("."))
        {
            qDebug() << "Failed to create directory";
            return;
        }
    }

    QSaveFile file(stateFilePath());
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open file for writing: " << file.errorString();
        return;
    }

    QJsonObject json;
    json["active"] = state.active;
    json["target_time"] = state.targetTime.toString(Qt::ISODate);
    json["origin"] = static_cast<int>(state.origin);

    QJsonDocument doc(json);
    file.write(doc.toJson(QJsonDocument::Compact));
    if (!file.commit())
    {
        qDebug() << "Failed to commit file: " << file.errorString();
        return;
    }

    qDebug() << "Successfully saved state to:" << filePath;
}

void FileShutdownStateRepository::clear()
{
    QFile::remove(stateFilePath());
    qDebug() << "file cleared";
}

std::optional<ShutdownState> FileShutdownStateRepository::load() const
{
    QFile file(stateFilePath());
    if (!file.exists())
    {
        return std::nullopt;
    }

    if (!file.open(QIODevice::ReadOnly))
    {
        return std::nullopt;
    }

    const auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject())
    {
        return std::nullopt;
    }

    const QJsonObject json = doc.object();

    ShutdownState state;
    state.active = json["active"].toBool(false);
    state.targetTime = QDateTime::fromString(json["target_time"].toString(), Qt::ISODate);
    state.origin = static_cast<ShutdownOrigin>(json["origin"].toInt(0));

    qDebug() << "file loaded";

    return state;
}
