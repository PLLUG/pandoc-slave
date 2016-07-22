#ifndef PANDOCRUNNER_H
#define PANDOCRUNNER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QMetaEnum>

/*!
 * \brief The PandocRunner class provides functionality
 * to run pandoc utility with specified parameters
 *
 * Usage:
 * \code{.cpp}
 * PandocRunner runner;                         // Create instance runner
 * QString output = runner.run(                 // Method run() return output content or error
 *                      PandocRunner::markdown, // Input format
 *                      PandocRunner::html,     // Output format
 *                      "path/to/input/file.md" // Path to input file
 *                  );
 * if (runner.statusCode != 0)
 * {
 *      qDebug() << "ERROR:" << output;         // In this case content holds error
 * }
 * else
 * {
 *      qDebug() << output;                    // content holds converted string
 * }
 * \endcode
 */

class PandocRunner : public QProcess
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
    QString run(PandocFormat from, PandocFormat to, const QString &file);
    QStringList buildParams(PandocFormat from, PandocFormat to, const QString &file) const;

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
};

#endif // PANDOCRUNNER_H
