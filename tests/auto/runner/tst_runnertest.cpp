#include <QString>
#include <QtTest>

#include "pandocrunner.h"

using namespace PandocSlave;

class RunnerTest : public QObject
{
    Q_OBJECT

public:
    RunnerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private:
    QString mPandocExePath;
    PandocRunner* mRunner;
};

RunnerTest::RunnerTest()
{
}

void RunnerTest::initTestCase()
{
    mPandocExePath = "path/to/pandoc.exe";
    mRunner = new PandocRunner(mPandocExePath);
}

void RunnerTest::cleanupTestCase()
{
    delete mRunner;
}

QTEST_APPLESS_MAIN(RunnerTest)

#include "tst_runnertest.moc"
