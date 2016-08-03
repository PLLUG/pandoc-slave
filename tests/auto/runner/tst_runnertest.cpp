#include <QString>
#include <QtTest>

#include "pandocrunner.h"

class RunnerTest : public QObject
{
    Q_OBJECT

public:
    RunnerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void test_build_parameters_without_file();
    void test_build_parameters_with_file();
    void test_check_pandoc_formats();

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

void RunnerTest::test_build_parameters_without_file()
{

    mRunner->buildParams(PandocRunner::PandocFormat::Markdown, PandocRunner::PandocFormat::HTML);

    QCOMPARE(mRunner->params().join(" "), QString("-f markdown -t html"));
}

void RunnerTest::test_build_parameters_with_file()
{
    mRunner->buildParams(PandocRunner::PandocFormat::Markdown, PandocRunner::PandocFormat::HTML, "path/to/some/file");

    QCOMPARE(mRunner->params().join(" "), QString("-f markdown -t html path/to/some/file"));
}

void RunnerTest::test_check_pandoc_formats()
{
    QCOMPARE(mRunner->fromFormat(PandocRunner::PandocFormat::Markdown), QString("markdown"));
    QCOMPARE(mRunner->fromFormat(PandocRunner::PandocFormat::Markdown_Github), QString("markdown_github"));
    QCOMPARE(mRunner->fromFormat(PandocRunner::PandocFormat::HTML), QString("html"));
}

void RunnerTest::cleanupTestCase()
{
    delete mRunner;
}

QTEST_APPLESS_MAIN(RunnerTest)

#include "tst_runnertest.moc"
