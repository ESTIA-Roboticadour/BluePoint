#ifndef CONFIG_H
#define CONFIG_H

#include "ParametersWidgetCollection_global.h"
#include "ParameterBase.h"
#include "IParametrable.h"

#include <QObject>
#include <QList>
#include <memory>
#include <type_traits>

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

    QString getPath() { return m_path; }

    bool save() const;
    bool save(const QString& path);

    static bool saveToFile(const Config* config, const QString& filePath);
    static std::unique_ptr<Config> loadFromFile(const QString& filePath, QObject* parent = nullptr);

    template<typename T = Config, std::enable_if_t<std::is_base_of_v<Config, T>, int> = 0>
    static std::unique_ptr<T> loadFromFile(const QString& filePath, bool& configFullyLoaded, QObject* parent = nullptr)
    {
        configFullyLoaded = false;
		std::unique_ptr<Config> config = loadFromFile(filePath, parent);
        if (config) {
            auto derived = std::make_unique<T>(parent);
            configFullyLoaded = static_cast<Config*>(derived.get())->setFromConfig(config.get());
            return derived;
        }
        return nullptr;
    }

public slots:
    void setParameters(const QList<ParameterBase*>& parameters);

protected:
    virtual bool setFromConfig(const Config* src) { Q_UNUSED(src); return true; }

private:
    QList<ParameterBase*> m_parameters;
    QString m_path;
};

#endif // CONFIG_H
