#include <QCoreApplication>

#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QObject>

#include "pandoc-slave/pandocrunner.h"
#include "pandoc-slave/paramsbuilder.h"

using namespace PandocSlave;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString projFolder = QCoreApplication::applicationDirPath();
    QString pandocExePath = QDir(projFolder).filePath("../../pandoc/pandoc.exe");

    QString inputFile = QDir(projFolder).filePath("../../test-input-files/input.md");

    ParamsBuilder builder_one;
    builder_one.addParam(ParamsBuilder::empty, inputFile);
    builder_one.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
    builder_one.addParam(ParamsBuilder::to, ParamsBuilder::HTML);

    QString builderError = builder_one.error();
    if (!builderError.isEmpty())
    {
        qDebug() << builderError;
    }
    else
    {
        PandocRunner* runner_one = new PandocRunner(pandocExePath, builder_one.params());

        QObject::connect(runner_one, &PandocRunner::finished, [=](int statusCode){
            if (statusCode != 0)
            {
                qDebug() << "ERROR:" << runner_one->error();
            }
            else
            {
                qDebug() << runner_one->content();
            }
        });

        runner_one->run();
    }

    QString input("# Hi all");

    ParamsBuilder builder_two;
    builder_two.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
    builder_two.addParam(ParamsBuilder::to, ParamsBuilder::HTML);

    builderError = builder_two.error();
    if (!builderError.isEmpty())
    {
        qDebug() << builderError;
    }
    else
    {
        PandocRunner* runner_two = new PandocRunner(pandocExePath, builder_two.params());

        QObject::connect(runner_two, &PandocRunner::finished, [=](int statusCode){
            if (statusCode != 0)
            {
                qDebug() << "ERROR:" << runner_two->error();
            }
            else
            {
                qDebug() << runner_two->content();
            }
        });

        runner_two->run(input.toUtf8());
    }

    return a.exec();
}
