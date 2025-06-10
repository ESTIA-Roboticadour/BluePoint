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
    Config(const QList<ParameterBase*>& parameters, QObject* parent = nullptr);
    Config(const Config& other, QObject* parent);
    Config(const Config& other);
    Config& operator=(const Config& other);
    ~Config() override = default;

    void addParameter(ParameterBase* parameter) override;
    ParameterBase* getParameter(const QString& name) const override;
    QList<ParameterBase*> getParameters() const override;

    QString getPath() const { return m_path; }
    bool getIsEditable() const { return m_isEditable; }

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
            configFullyLoaded = static_cast<Config*>(derived.get())->setFromConfig(config.get(), true);
            return derived;
        }
        return nullptr;
    }

    virtual bool setFromConfig(const Config* src, bool copyPath) {
        if (src)
        {
            m_isEditable = src->m_isEditable;
            if (copyPath)
                m_path = src->m_path;
        }
        return true;
    }

    virtual void reset() {}

    virtual Config* copy(QObject* parent = nullptr) const;

public slots:
    void setParameters(const QList<ParameterBase*>& parameters);
    void setIsEditable(bool isEditable);

private slots:
    void onParameterChanged(const ParameterBase* sender);

private:
    static void cloneFrom(Config& dst, const Config& src);

signals:
    void parameterChanged(const ParameterBase* sender);
    void pathChanged(const QString& path);
    void saved(const Config* sender);
    void isEditableChanged(bool isEditable);

private:
    QList<ParameterBase*> m_parameters;
    QString m_path;
    bool m_isEditable;
};

#endif // CONFIG_H
