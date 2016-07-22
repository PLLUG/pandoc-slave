#include <QCoreApplication>

#include <QDir>
#include <QCoreApplication>
#include <QDebug>

#include "pandoc-workflow/pandocrunner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString projFolder = QCoreApplication::applicationDirPath();
    QString pandocExePath = QDir(projFolder).filePath("../../pandoc/pandoc.exe");
    QString inputFile = QDir(projFolder).filePath("../../test-input-files/input.md");

    PandocRunner runner(pandocExePath);
    QString result = runner.run(PandocRunner::Markdown, PandocRunner::HTML, inputFile);

    if (runner.statusCode() != 0)
    {
        qDebug() << "ERROR:" << result;
    }
    else
    {
        qDebug() << result;
    }

    return a.exec();
}
