#ifndef BOOLPARAMETER_H
#define BOOLPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <memory>

class PARAMETERS_WIDGETS_API BoolParameter : public ParameterBase
{
	Q_OBJECT

public:
	explicit BoolParameter(const QString& name, const bool value = false, QObject* parent = nullptr);
    BoolParameter(const BoolParameter& parameter, QObject* parent = nullptr);
    BoolParameter(const QString& name, const BoolParameter& parameter, QObject* parent = nullptr);
	~BoolParameter() = default;

	bool getValue() const;

    ParameterBase* copy(QObject* parent = nullptr) const override;

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

public slots:
	void setValue(bool value);

signals:
	void valueChanged(bool value);

private:
	bool m_value;
};

#endif // BOOLPARAMETER_H
