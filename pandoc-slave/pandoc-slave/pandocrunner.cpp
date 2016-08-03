#include "pandocrunner.h"

#include <QStringList>
#include <QProcess>


PandocRunner::PandocRunner(QString &pandocExePath, QObject* parent):
    QObject(parent)
  , mContent("")
  , mError("")
  , mStatusCode(0)
  , mPandocExePath(pandocExePath)
{
    mMetaEnum = QMetaEnum::fromType<PandocFormat>();

    mProcess = new QProcess(this);

    initializeConnections();
}

QStringList PandocRunner::params() const
{
    return mParams;
}

void PandocRunner::run(PandocFormat from, PandocFormat to, const QString &file)
{
    buildParams(from, to, file);

    mProcess->start(mPandocExePath, mParams);
}

void PandocRunner::run(PandocRunner::PandocFormat from, PandocRunner::PandocFormat to, const QByteArray &buffer)
{
    buildParams(from, to);

    mProcess->start(mPandocExePath, mParams);
    mProcess->write(buffer);
    mProcess->closeWriteChannel();
}

int PandocRunner::statusCode() const
{
    return mStatusCode;
}

void PandocRunner::finishedProcess(int exitCode)
{
    mStatusCode = exitCode;
    emit finished(exitCode);
}

void PandocRunner::readyReadOutput()
{
    mContent = QString(mProcess->readAllStandardOutput());
}

void PandocRunner::readyReadError()
{
    mError = QString(mProcess->readAllStandardError());
}

QString PandocRunner::content()
{
    return mContent;
}

QString PandocRunner::error()
{
    return mError;
}

void PandocRunner::setPandocExePath(const QString &path)
{
    mPandocExePath = path;
}

QString PandocRunner::pandocExePath() const
{
    return mPandocExePath;
}


QString PandocRunner::fromFormat(PandocRunner::PandocFormat format) const
{
    return QString(mMetaEnum.valueToKey(format)).toLower();
}

void PandocRunner::buildParams(PandocRunner::PandocFormat from, PandocRunner::PandocFormat to)
{
    mParams.clear();
    mParams << QString("-f") << fromFormat(from);
    mParams << QString("-t") << fromFormat(to);
}

void PandocRunner::buildParams(PandocFormat from, PandocFormat to, const QString &file)
{
    buildParams(from, to);
    mParams << file;
}

void PandocRunner::initializeConnections()
{
    connect(mProcess, SIGNAL(finished(int)), this, SLOT(finishedProcess(int)));
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadOutput()));
    connect(mProcess, SIGNAL(readyReadStandardError()), this, SLOT(readyReadError()));
}
