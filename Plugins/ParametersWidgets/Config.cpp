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
    m_path(),
    m_isEditable(true)
{}

Config::Config(const QList<ParameterBase*>& parameters, QObject* parent) :
    QObject(parent),
    m_parameters(),
    m_path(),
    m_isEditable(true)
{
    for (const ParameterBase* p : parameters)
        if (p)
            addParameter(p->copy(this));
}

Config::Config(const Config& other, QObject* parent) :
QObject(parent ? parent : other.parent()),
    m_parameters(),
    m_path(),
    m_isEditable(true)
{
    cloneFrom(*this, other);
}

Config::Config(const Config& other) :
    QObject(other.parent()),
    m_parameters(),
    m_path(),
    m_isEditable(true)
{
    cloneFrom(*this, other);
}

Config& Config::operator=(const Config& other)
{
    if (this == &other)
        return *this;
    // 1) Purger les paramètres existants
    qDeleteAll(m_parameters);        // détruit aussi les enfants QObject
    m_parameters.clear();
    // 2) Copier le reste
    cloneFrom(*this, other);
    return *this;
}

void Config::cloneFrom(Config& dst, const Config& src)
{
    // Chemin éventuel
    dst.m_path = src.m_path;
    dst.m_isEditable = src.m_isEditable;

    // Duplication profonde des paramètres
    for (const ParameterBase* p : src.m_parameters)
    {
        if (p)
            dst.addParameter(p->copy(&dst));     // parent = dst
    }
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
    parameter->setIsEditable(m_isEditable);
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

void Config::setIsEditable(bool isEditable)
{
    if (m_isEditable != isEditable)
    {
        m_isEditable = isEditable;
        for (auto& param : m_parameters)
            param->setIsEditable(m_isEditable);

        emit isEditableChanged(m_isEditable);
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
    QFileInfo fi(path);
    QString absPath = fi.isAbsolute() ?
                          path :
                          (QDir::currentPath() + '/' + path);

    if (absPath.isEmpty())
        return false;

    bool fileSaved = Config::saveToFile(this, absPath);
    if (fileSaved)
    {
        if (m_path != absPath)
        {
            m_path = absPath;
            emit pathChanged(absPath);
        }
        emit saved(this);
    }
    return fileSaved;
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
        qCritical() << "Unable to create the" << filePath << "folder";
        return false;
    }

    // 4) Ecriture atomique : données dans un fichier temporaire
    QSaveFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Can not open:" << filePath << ':' << file.errorString();
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
        qCritical() << "Cannot write" << filePath << ':' << file.errorString();
        return false;
    }

    // 6) Renomme le fichier temp -> définitif ; en cas d'échec, l'ancien reste intact
    if (!file.commit()) {
        qCritical() << "Can not commit" << filePath << ':' << file.errorString();
        return false;
    }
    return true;
}


std::unique_ptr<Config> Config::loadFromFile(const QString& filePath, QObject* parent)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Unable to open" << filePath;
        return nullptr;
    }

    const QByteArray data = file.readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
    {
        qCritical() << "Unable to convert data into json object";
        return nullptr;
    }

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

Config* Config::copy(QObject* parent)
{
    // 1) Nouvelle config, même parent
    auto clone = new Config(parent);

    // 2) Copie la valeur du chemin
    clone->m_path = this->m_path;
    clone->m_isEditable = this->m_isEditable;

    // 3) Copie profonde des paramètres
    for (const ParameterBase* p : m_parameters)
    {
        if (p)
            clone->addParameter(p->copy(clone));   // parent = clone
    }

    return clone;
}
