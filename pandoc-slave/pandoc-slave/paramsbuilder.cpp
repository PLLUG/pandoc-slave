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
    if (key == ParamsBuilder::empty)
    {
        QString msg = QString("%1 and %2")
                .arg(fromKeys(key))
                .arg(fromFormat(format));
        setError(msg);
    }
    mParams << fromKeys(key) << fromFormat(format);
}

void PandocSlave::ParamsBuilder::addParam(PandocKeys key, const QString &value)
{

    if (key != ParamsBuilder::empty)
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

void PandocSlave::ParamsBuilder::setError(const QString &msg)
{
    mError = QString("Not allowed parameters combination: %1").arg(msg);
}

void PandocSlave::ParamsBuilder::raw(const QString &rawLine)
{
    if(!rawLine.isEmpty())
    {
        mParams = rawLine.trimmed().split(" ", QString::SkipEmptyParts);
    }
}

void PandocSlave::ParamsBuilder::clear()
{
    mParams.clear();
    mError.clear();
}

void PandocSlave::ParamsBuilder::initializeKeys()
{
    mKeys["from"] = "-f";
    mKeys["to"] = "-t";
    mKeys["output"] = "-o";
    mKeys["standalone"] = "-s";
    mKeys["template_file"] = "--template";
    mKeys["metadata"] = "--metadata";
    mKeys["empty"] = "";
}
