#ifndef CONFIG_H
#define CONFIG_H

#include "ParametersWidgetCollection_global.h"
#include "ParameterBase.h"
#include "IParametrable.h"

#include <QObject>
#include <QList>
#include <memory>

class PARAMETERS_WIDGETS_API Config : public QObject, public IParametrable
{
    Q_OBJECT
    Q_INTERFACES(IParametrable)

public:
    explicit Config(QObject* parent = nullptr);
    explicit Config(const QList<ParameterBase*>& parameters, QObject* parent = nullptr);
    Config(const Config& other);
    Config& operator=(const Config& other);
    ~Config() override = default;

    void addParameter(ParameterBase* parameter) override;
    ParameterBase* getParameter(const QString& name) const override;
    QList<ParameterBase*> getParameters() const override;

    void setParameters(const QList<ParameterBase*>& parameters);

    static bool saveToFile(const Config& config, const QString& filePath);
    static std::unique_ptr<Config> loadFromFile(const QString& filePath, QObject* parent = nullptr);

private:
    QList<ParameterBase*> m_parameters;
};

#endif // CONFIG_H
