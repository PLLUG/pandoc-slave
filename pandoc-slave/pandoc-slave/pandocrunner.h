#ifndef PANDOCRUNNER_H
#define PANDOCRUNNER_H

#include <QObject>
#include <QString>

#include "paramsbuilder.h"

class QProcess;

namespace PandocSlave
{

/*!
 * \brief The PandocRunner class provides functionality
 * to run pandoc utility with specified parameters
 *
 * Usage:
 * \code{.cpp}
 *
 *  use namespace PandocSlave;
 *
 *  QString pandocExePath = "path/to/pandoc/executable/file";
 *  QString inputFile = "path/to/input/file";
 *
 *  ParamsBuilder builder;
 *  builder.addParam(ParamsBuilder::empty, inputFile);
 *  builder.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
 *  builder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);
 *
 *  QString builderError = builder.error();
 *  if (!builderError.isEmpty())
 *  {
 *      qDebug() << builderError;
 *  }
 *  else
 *  {
 *      PandocRunner* runner = new PandocRunner(pandocExePath, builder.params());
 *
 *      QObject::connect(runner, &PandocRunner::finished, [=](int statusCode){
 *          if (statusCode != 0)
 *          {
 *              qDebug() << "ERROR:" << runner_one->error();
 *          }
 *          else
 *          {
 *              qDebug() << runner->content();
 *          }
 *      });
 *
 *      runner->run();
 *  }
 *
 * \endcode
 */
class PandocRunner : public QObject
{
    Q_OBJECT

public:

    PandocRunner(const QString &pandocExePath, QObject* parent = 0);
    PandocRunner(const QString &pandocExePath, const QStringList &params, QObject* parent = 0);

    QStringList params() const;
    void setParams(const QStringList &params);
    int statusCode() const;
    QString content();
    QString error();
    void setPandocExePath(const QString &path);
    QString pandocExePath() const;

    void run();
    void run(const QStringList &params);
    void run(const QByteArray &buffer);
    void run(const QStringList &params, const QByteArray &buffer);

signals:
    void finished(int statusCode);

private slots:
    void finishedProcess(int exitCode);
    void readyReadOutput();
    void readyReadError();

private:
    void initializeConnections();

private:
    QString mContent;
    QString mError;
    int mStatusCode;
    QString mPandocExePath;
    QStringList mParams;
    QProcess* mProcess;
};
}

#endif // PANDOCRUNNER_H
