#include "paramsbuilder.h"

PandocSlave::ParamsBuilder::ParamsBuilder(QObject *parent) : QObject(parent)
{
    initializeKeys();

    mMetaEnumForFormats = QMetaEnum::fromType<PandocFormat>();
    mMetaEnumForKeys = QMetaEnum::fromType<PandocKeys>();
}

QString PandocSlave::ParamsBuilder::fromFormat(PandocFormat format) const
{
    return QString(mMetaEnumForFormats.valueToKey(format)).toLower();
}

QString PandocSlave::ParamsBuilder::fromKeys(PandocKeys key) const
{
    QString keyEnumStr = QString(mMetaEnumForKeys.valueToKey(key)).toLower();
    return mKeys[keyEnumStr];
}

void PandocSlave::ParamsBuilder::addParam(PandocKeys key, PandocFormat format)
{
    if (key == PandocKeys::empty)
    {
        mError = "Not allowed parameters combination: "
                "PandocKeys::empty and PandocFormat::" +
                fromFormat(format);
    }
    mParams << fromKeys(key) << fromFormat(format);
}

void PandocSlave::ParamsBuilder::addParam(PandocKeys key, const QString &value)
{
    if (key != PandocKeys::empty)
    {
        mParams << fromKeys(key);
    }
    if (!value.isEmpty())
    {
        mParams << value;
    }
}

QStringList PandocSlave::ParamsBuilder::params() const
{
    return mParams;
}

void PandocSlave::ParamsBuilder::setParams(QStringList params)
{
    mParams = params;
}

QString PandocSlave::ParamsBuilder::toString() const
{
    return mParams.join(" ");
}

QString PandocSlave::ParamsBuilder::error() const
{
    return mError;
}

void PandocSlave::ParamsBuilder::initializeKeys()
{
    mKeys["from"] = "-f";
    mKeys["to"] = "-t";
    mKeys["output"] = "-o";
    mKeys["standalone"] = "-s";
    mKeys["empty"] = "";
}
