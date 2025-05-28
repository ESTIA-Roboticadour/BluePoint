#include "Config.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSaveFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Config::Config(QObject* parent) :
    QObject(parent),
    m_parameters(),
    m_path()
{
}

Config::Config(const QList<ParameterBase*>& parameters, QObject* parent) :
    QObject(parent),
    m_parameters(parameters),
    m_path()
{
}

Config::Config(const Config& other) :
    QObject(other.parent()),
    m_parameters(other.m_parameters),
    m_path(other.m_path)
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

    connect(parameter, &ParameterBase::parameterChanged, this, &Config::onParameterChanged);
    // pour ne pas avoir un disconnect sur un pointeur libéré
    connect(parameter, &QObject::destroyed, this, [this, parameter]{ m_parameters.removeOne(parameter); });
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
    for (auto& parameter : m_parameters) {
        disconnect(parameter, &ParameterBase::parameterChanged, this, &Config::onParameterChanged);
    }
    m_parameters.clear();
    for (auto& parameter : parameters)
    {
        addParameter(parameter);
    }
}

void Config::onParameterChanged(const ParameterBase* sender)
{
    emit parameterChanged(sender);
}

bool Config::save() const
{
    return m_path.isEmpty() ? false : Config::saveToFile(this, m_path);
}

bool Config::save(const QString& path)
{
    if (m_path != path)
    {
        m_path = path;
    }
    return Config::saveToFile(this, m_path);
}

bool Config::saveToFile(const Config* cfg, const QString& userPath)
{
    // 1) garde-fou
    if (!cfg)
        return false;

    // 2) Ajoute l'extension si oubliée
    QString filePath = userPath;
    if (!filePath.endsWith(".json", Qt::CaseInsensitive))
        filePath += ".json";

    // 3) Crée l'arborescence si nécessaire
    QFileInfo fi(filePath);
    QDir dir = fi.dir();
    if (!dir.exists() && !dir.mkpath(".")) {
        qWarning() << "Unable to create the" << filePath << "folder";
        return false;
    }

    // 4) Ecriture atomique : données dans un fichier temporaire
    QSaveFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Can not open:" << filePath << ':' << file.errorString();
        return false;
    }

    // 5) Construction du JSON
    // Construction du tableau JSON (sans reserve)
    QJsonArray paramsArray;
    for (ParameterBase* p : cfg->m_parameters)
        if (p)
            paramsArray.append(p->toJson());

    // Objet racine explicite -> aucune ambiguité
    QJsonObject root;
    root.insert("parameters", paramsArray);

    const QJsonDocument doc(root);
    if (file.write(doc.toJson(QJsonDocument::Indented)) == -1) {
        qWarning() << "Cannot write" << filePath << ':' << file.errorString();
        return false;
    }

    // 6) Renomme le fichier temp -> définitif ; en cas d'échec, l'ancien reste intact
    if (!file.commit()) {
        qWarning() << "Can not commit" << filePath << ':' << file.errorString();
        return false;
    }
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
    cfg->m_path = filePath;
    return cfg;
}
