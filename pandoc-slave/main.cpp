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

    ParamsBuilder builder;

//    qDebug() << builder.fromFormat(ParamsBuilder::Markdown);
//    qDebug() << builder.fromKeys(ParamsBuilder::from);

    builder.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
    builder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);
    builder.addParam(ParamsBuilder::empty, ParamsBuilder::Markdown_Github);
    builder.addParam(ParamsBuilder::empty, "some_value");
    builder.addParam(ParamsBuilder::standalone, "");

    QString builderError = builder.error();

    if (builderError.isEmpty())
    {
        qDebug() << builder.toString();
    }
    else
    {
        qDebug() << builderError;
    }

//    QString projFolder = QCoreApplication::applicationDirPath();
//    QString pandocExePath = QDir(projFolder).filePath("../../pandoc/pandoc.exe");

//    QString inputFile = QDir(projFolder).filePath("../../test-input-files/input.md");
//    QString input("# Hi all");

//    PandocRunner* runner_one = new PandocRunner(pandocExePath);
//    PandocRunner* runner_two = new PandocRunner(pandocExePath);

//    QObject::connect(runner_one, &PandocRunner::finished, [=](int statusCode){
//        if (statusCode != 0)
//        {
//            qDebug() << "ERROR:" << runner_one->error();
//        }
//        else
//        {
//            qDebug() << runner_one->content();
//        }
//    });

//    QObject::connect(runner_two, &PandocRunner::finished, [=](int statusCode){
//        if (statusCode != 0)
//        {
//            qDebug() << "ERROR:" << runner_two->error();
//        }
//        else
//        {
//            qDebug() << runner_two->content();
//        }
//    });

//    runner_one->run(PandocRunner::Markdown, PandocRunner::HTML, inputFile);
//    runner_two->run(PandocRunner::Markdown, PandocRunner::HTML, input.toUtf8());

    return a.exec();
}
