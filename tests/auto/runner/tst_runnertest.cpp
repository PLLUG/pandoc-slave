#include <QString>
#include <QtTest>

class RunnerTest : public QObject
{
    Q_OBJECT

public:
    RunnerTest();

private Q_SLOTS:
    void testCase1();
};

RunnerTest::RunnerTest()
{
}

void RunnerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(RunnerTest)

#include "tst_runnertest.moc"
