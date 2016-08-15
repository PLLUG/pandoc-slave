#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include "pandocrunner.h"
#include "paramsbuilder.h"

using namespace PandocSlave;

class RunnerTest : public QObject
{
    Q_OBJECT

public:
    RunnerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void test_initialState_1();
    void test_initialState_2();
    void test_set_get_params();
    void test_set_get_pandocExePath();
};

RunnerTest::RunnerTest()
{}

void RunnerTest::initTestCase()
{}

void RunnerTest::test_initialState_1()
{
    QString pandocExePath = "path/to/pandoc.exe";
    PandocRunner runner(pandocExePath);

    QCOMPARE(pandocExePath, runner.pandocExePath());
    QVERIFY(runner.params().size() == 0);
    QVERIFY(runner.statusCode() == 0);
    QVERIFY(runner.error().isEmpty());
    QVERIFY(runner.content().isEmpty());
}

void RunnerTest::test_initialState_2()
{
    QString pandocExePath = "path/to/pandoc.exe";
    QStringList params;
    params << "String 1" << "String 2";

    PandocRunner runner(pandocExePath, params);

    QCOMPARE(pandocExePath, runner.pandocExePath());
    QVERIFY(runner.params().size() == 2);
    QVERIFY(runner.statusCode() == 0);
    QVERIFY(runner.error().isEmpty());
    QVERIFY(runner.content().isEmpty());
}

void RunnerTest::test_set_get_params()
{
    QString pandocExePath = "path/to/pandoc.exe";

    PandocRunner runner(pandocExePath);
    QStringList params;
    params << "String 1" << "String 2";
    runner.setParams(params);

    QCOMPARE(params.join(" "), runner.params().join(" "));
}

void RunnerTest::test_set_get_pandocExePath()
{
    QString pandocExePath = "path/to/pandoc.exe";

    PandocRunner runner(pandocExePath);

    QCOMPARE(pandocExePath, runner.pandocExePath());
    runner.setPandocExePath("some path");
    QCOMPARE(QString("some path"), runner.pandocExePath());

}

void RunnerTest::cleanupTestCase()
{}

QTEST_APPLESS_MAIN(RunnerTest)

#include "tst_runnertest.moc"
