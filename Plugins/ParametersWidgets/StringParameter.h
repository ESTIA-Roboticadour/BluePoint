#ifndef STRINGPARAMETER_H
#define STRINGPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <memory>

class PARAMETERS_WIDGETS_API StringParameter : public ParameterBase
{
	Q_OBJECT

public:
    enum class Kind { Plain, FilePath, DirectoryPath };
    Q_ENUM(Kind)

    explicit StringParameter(const QString& name, const QString& value="", Kind kind = Kind::Plain, QObject* parent = nullptr);
    StringParameter(const StringParameter& parameter, QObject* parent = nullptr);
    StringParameter(const QString& name, const StringParameter& parameter, QObject* parent = nullptr);
	~StringParameter() = default;

	QString getValue() const;
    Kind    getKind()  const;
    bool    getCanEditPath() const;

    ParameterBase* copy(QObject* parent = nullptr) const override;

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);


public slots:
	void setValue(const QString& value);
    void setKind(Kind k);

    // only active for FilePath and DirectoryPath kinds.
    void setCanEditPath(bool canEditPath);

signals:
	void valueChanged(const QString& value);
    void kindChanged(Kind kind);
    void canEditPathChanged(bool canEditPath);

private:
	QString m_value;
    Kind    m_kind;
    bool    m_canEditPath;
};

#endif // STRINGPARAMETER_H
