#include "Config.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Config::Config(QObject* parent) :
    QObject(parent)
{
}

Config::Config(const QList<ParameterBase*>& parameters, QObject* parent) :
    QObject(parent),
    m_parameters(parameters)
{
}

Config::Config(const Config& other) :
    QObject(other.parent()),
    m_parameters(other.m_parameters)
{
}

Config& Config::operator=(const Config& other)
{
    if (this != &other)
    {
        m_parameters = other.m_parameters;
    }
    return *this;
}

void Config::addParameter(ParameterBase* parameter)
{
    if (!parameter)
        return;

    for (const auto& param : m_parameters)
    {
        if (param == parameter || param->getName() == parameter->getName())
            return;
    }
    m_parameters.append(parameter);
}

ParameterBase* Config::getParameter(const QString& name) const
{
    for (const auto& param : m_parameters)
    {
        if (param->getName() == name)
            return param;
    }
    return nullptr;
}

QList<ParameterBase*> Config::getParameters() const
{
    return m_parameters;
}

void Config::setParameters(const QList<ParameterBase*>& parameters)
{
    m_parameters = parameters;
}

bool Config::saveToFile(const Config& config, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonArray paramsArray;
    for (auto* param : config.m_parameters)
    {
        if (param)
            paramsArray.append(param->toJson());
    }

    QJsonObject root;
    root.insert("parameters", paramsArray);

    const QJsonDocument doc(root);
    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

std::unique_ptr<Config> Config::loadFromFile(const QString& filePath, QObject* parent)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return nullptr;

    const QByteArray data = file.readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
        return nullptr;

    const QJsonArray paramsArray = doc.object().value("parameters").toArray();

    auto cfg = std::make_unique<Config>(parent);
    for (const auto& val : paramsArray)
    {
        if (val.isObject())
        {
            std::unique_ptr<ParameterBase> param = ParameterBase::fromJson(val.toObject(), cfg.get());
            if (param.get())
                cfg->addParameter(param.release());
        }
    }
    return cfg;
}
