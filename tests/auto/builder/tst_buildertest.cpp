#include <QString>
#include <QtTest>

#include "paramsbuilder.h"

using namespace PandocSlave;

class BuilderTest : public QObject
{
    Q_OBJECT

public:
    BuilderTest();

private Q_SLOTS:
    void test_checkPandocFormats();
    void test_checkParamsKeys();
    void test_addParamFormat();
    void test_addParamValue();
    void test_addParamKey();
    void test_builderError();

private:
    ParamsBuilder mBuilder;
};

BuilderTest::BuilderTest()
{
}

void BuilderTest::test_checkPandocFormats()
{
    QCOMPARE(mBuilder.fromFormat(ParamsBuilder::Markdown), QString("markdown"));
    QCOMPARE(mBuilder.fromFormat(ParamsBuilder::Markdown_Github), QString("markdown_github"));
    QCOMPARE(mBuilder.fromFormat(ParamsBuilder::HTML), QString("html"));
}

void BuilderTest::test_checkParamsKeys()
{
    QCOMPARE(mBuilder.fromKeys(ParamsBuilder::empty), QString(""));
    QCOMPARE(mBuilder.fromKeys(ParamsBuilder::to), QString("-t"));
    QCOMPARE(mBuilder.fromKeys(ParamsBuilder::from), QString("-f"));
    QCOMPARE(mBuilder.fromKeys(ParamsBuilder::output), QString("-o"));
    QCOMPARE(mBuilder.fromKeys(ParamsBuilder::standalone), QString("-s"));
}

void BuilderTest::test_addParamFormat()
{
    mBuilder.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
    mBuilder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);

    QCOMPARE(mBuilder.toString(), QString("-f markdown -t html"));
}

void BuilderTest::test_addParamValue()
{
    mBuilder.addParam(ParamsBuilder::empty, "value");

    QCOMPARE(mBuilder.toString(), QString("value"));
}

void BuilderTest::test_addParamKey()
{
    mBuilder.addParam(ParamsBuilder::standalone, "");

    QCOMPARE(mBuilder.toString(), QString("-s"));
}

void BuilderTest::test_builderError()
{
    mBuilder.addParam(ParamsBuilder::from, "");
    mBuilder.addParam(ParamsBuilder::to, "");

    QVERIFY(!mBuilder.error().isEmpty());
}

QTEST_APPLESS_MAIN(BuilderTest)

#include "tst_buildertest.moc"
