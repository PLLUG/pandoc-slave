#ifndef PANDOCRUNNER_H
#define PANDOCRUNNER_H

#include <QObject>
#include <QString>
#include <QMetaEnum>

class QProcess;

/*!
 * \brief The PandocRunner class provides functionality
 * to run pandoc utility with specified parameters
 *
 * Usage:
 * \code{.cpp}
 *
 *  // Specify path to pandoc executable file
 *  QString pandocExePath = "path\to\pandoc.exe";
 *
 *  // Create instances
 *  PandocRunner* runner_for_input_file = new PandocRunner(pandocExePath);
 *  PandocRunner* runner_for_buffer = new PandocRunner(pandocExePath);
 *
 *  QObject::connect(runner_for_input_file, &PandocRunner::finished, [=](int statusCode){
 *      if (statusCode != 0)
 *      {
 *          qDebug() << "ERROR:" << runner_for_input_file->error();
 *      }
 *      else
 *      {
 *          qDebug() << runner_for_input_file->content();
 *      }
 *  });
 *
 *  QObject::connect(runner_for_buffer, &PandocRunner::finished, [=](int statusCode){
 *      if (statusCode != 0)
 *      {
 *          qDebug() << "ERROR:" << runner_for_buffer->error();
 *      }
 *      else
 *      {
 *          qDebug() << runner_for_buffer->content();
 *      }
 *  });
 *
 *  runner_for_input_file->run(
 *      PandocRunner::markdown,         // Input format
 *      PandocRunner::html,             // Output format
 *      "path/to/input/file.md"         // Path to input file
 *  );
 *
 *  runner_for_buffer->run(
 *      PandocRunner::markdown,         // Input format
 *      PandocRunner::html,             // Output format
 *      QString("# Header").toUtf8()    // Input content
 *  );
 *
 * \endcode
 */

class PandocRunner : public QObject
{
    Q_OBJECT

public:
    enum PandocFormat {
        HTML,
        Markdown,
        Json,
        Markdown_Github
    };
    Q_ENUM(PandocFormat)

    PandocRunner(QString &pandocExePath, QObject* parent = 0);

    int statusCode() const;
    QString content();
    QString error();
    void setPandocExePath(const QString &path);
    QString pandocExePath() const;

    void run(PandocFormat from, PandocFormat to, const QString &file);
    void run(PandocFormat from, PandocFormat to, const QByteArray &buffer);
    void buildParams(PandocFormat from, PandocFormat to);
    void buildParams(PandocFormat from, PandocFormat to, const QString &file);

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
    QMetaEnum mMetaEnum;
    QStringList mParams;
    QProcess* mProcess;
};

#endif // PANDOCRUNNER_H
