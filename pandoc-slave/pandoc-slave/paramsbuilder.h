#ifndef PARAMSBUILDER_H
#define PARAMSBUILDER_H

#include <QObject>
#include <QMap>
#include <QMetaEnum>

namespace PandocSlave
{

/**
 * @brief The ParamsBuilder class provides easy and intuitive
 * functionality to build complex parameter string for pandoc
 * process.
 *
 * Usage:
 *
 *
 *  \code{cpp}
 *
 *  ParamsBuilder builder;
 *
 *  builder.addParam(ParamsBuilder::from, ParamsBuilder::Markdown);
 *
 *  // output "-f markdown"
 *  qDebug() << builder.toString();
 *
 *  builder.addParam(ParamsBuilder::to, ParamsBuilder::HTML);
 *
 *  // output "-f markdown -t html"
 *  qDebug() << builder.toString();
 *
 *  builder.addParam(ParamsBuilder::empty, "path/to/input/file");
 *
 *  // output "-f markdown -t html path/to/input/file"
 *  qDebug() << builder.toString();
 *
 *  // this line generate builder error like:
 *  // "Not allowed parameters combination:
 *  // PandocKeys::empty and PandocFormat::markdown_github"
 *  builder.addParam(ParamsBuilder::empty, ParamsBuilder::Markdown_Github);
 *
 *  // before use parameters
 *  QString builderError = builder.error();
 *  if (!builderError.isEmpty())
 *  {
 *      qDebug() << builderError;
 *  }
 *  else
 *  {
 *      PandocRunner runner("path/to/pandoc", builder.params());
 *  }
 *
 *  \endcode
 */
class ParamsBuilder : public QObject
{
    Q_OBJECT

public:
    enum PandocFormat {
        HTML,
        Markdown,
        Json,
        Markdown_Github
    };
    Q_ENUM(PandocFormat)

    enum PandocKeys {
        from,
        to,
        output,
        standalone,
        empty
    };
    Q_ENUM(PandocKeys)

public:
    explicit ParamsBuilder(QObject *parent = 0);

    QString fromFormat(PandocFormat format) const;
    QString fromKeys(PandocKeys key) const;
    void addParam(PandocKeys key, PandocFormat format);
    void addParam(PandocKeys key, const QString &value);
    QStringList params() const;
    void setParams(QStringList params);
    QString toString() const;
    QString error() const;

signals:

public slots:

private:
    void initializeKeys();

private:
    QStringList mParams;
    QMetaEnum mMetaEnumForFormats;
    QMetaEnum mMetaEnumForKeys;
    QMap<QString, QString> mKeys;
    QString mError;
};

}

#endif // PARAMSBUILDER_H
