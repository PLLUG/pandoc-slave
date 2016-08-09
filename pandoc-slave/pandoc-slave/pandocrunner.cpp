#include "pandocrunner.h"

#include <QStringList>
#include <QProcess>

PandocSlave::PandocRunner::PandocRunner(const QString &pandocExePath, QObject* parent):
    QObject(parent)
  , mContent("")
  , mError("")
  , mStatusCode(0)
  , mPandocExePath(pandocExePath)
{
    mProcess = new QProcess(this);

    initializeConnections();
}

PandocSlave::PandocRunner::PandocRunner(const QString &pandocExePath, const QStringList &params, QObject *parent)
{
    PandocRunner(pandocExePath, parent);
    mParams = params;
}

QStringList PandocSlave::PandocRunner::params() const
{
    return mParams;
}

void PandocSlave::PandocRunner::setParams(const QStringList &params)
{
    mParams = params;
}

void PandocSlave::PandocRunner::run(const QStringList &params)
{
    mProcess->start(mPandocExePath, params);
}

void PandocSlave::PandocRunner::run()
{
    run(mParams);
}

void PandocSlave::PandocRunner::run(const QStringList &params, const QByteArray &buffer)
{
    mProcess->start(mPandocExePath, params);
    mProcess->write(buffer);
    mProcess->closeWriteChannel();
}

void PandocSlave::PandocRunner::run(QByteArray &buffer)
{
    run(mParams, buffer);
}

int PandocSlave::PandocRunner::statusCode() const
{
    return mStatusCode;
}

void PandocSlave::PandocRunner::finishedProcess(int exitCode)
{
    mStatusCode = exitCode;
    emit finished(exitCode);
}

void PandocSlave::PandocRunner::readyReadOutput()
{
    mContent = QString(mProcess->readAllStandardOutput());
}

void PandocSlave::PandocRunner::readyReadError()
{
    mError = QString(mProcess->readAllStandardError());
}

QString PandocSlave::PandocRunner::content()
{
    return mContent;
}

QString PandocSlave::PandocRunner::error()
{
    return mError;
}

void PandocSlave::PandocRunner::setPandocExePath(const QString &path)
{
    mPandocExePath = path;
}

QString PandocSlave::PandocRunner::pandocExePath() const
{
    return mPandocExePath;
}

void PandocSlave::PandocRunner::initializeConnections()
{
    connect(mProcess, SIGNAL(finished(int)), this, SLOT(finishedProcess(int)));
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadOutput()));
    connect(mProcess, SIGNAL(readyReadStandardError()), this, SLOT(readyReadError()));
}
