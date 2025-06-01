#ifndef GROUPPARAMETER_H
#define GROUPPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <memory>

class PARAMETERS_WIDGETS_API GroupParameter : public ParameterBase
{
	Q_OBJECT
public:
    explicit GroupParameter(const QString& name, QObject* parent = nullptr);
    GroupParameter(const GroupParameter& other, QObject* parent = nullptr);
    GroupParameter(const QString& name, const GroupParameter& other, QObject* parent = nullptr);
    ~GroupParameter();

	void addParameter(ParameterBase* parameter);
	void removeParameter(ParameterBase* parameter);
	void clearParameters();

	QList<const ParameterBase*> getParameters() const;
    ParameterBase* getParameter(const QString& name) const;

    ParameterBase* copy(QObject* parent) const;

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

public slots:
	void setIsEditable(bool isEditable) override;

private slots:
    void onChildChanged(const ParameterBase* sender);

private:
	QList<ParameterBase*> m_parameters;
};

#endif // GROUPPARAMETER_H
