#include "NavigationTreeParser.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

/* ─── Méthodes publiques ──────────────────────────────────────────── */
std::unique_ptr<NavigationTree> NavigationTreeParser::fromJson(QStringView json, QString* error)
{
    QJsonParseError pe;
    QJsonDocument   doc = QJsonDocument::fromJson(json.toUtf8(), &pe);
    if (pe.error != QJsonParseError::NoError) {
        jsonError(QObject::tr("JSON parse error: %1").arg(pe.errorString()), error);
        return nullptr;
    }

    if (!doc.isObject()) {
        jsonError(QObject::tr("Root JSON value must be an object"), error);
        return nullptr;
    }

    QString err;
    NavigationNode* root = parseNode(doc.object(), nullptr, &err);
    if (!root) {
        jsonError(err, error);
        return nullptr;
    }

    return std::make_unique<NavigationTree>(root);
}

std::unique_ptr<NavigationTree> NavigationTreeParser::fromFile(const QString& path, QString* error)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        jsonError(QObject::tr("Cannot open %1").arg(path), error);
        return nullptr;
    }

    QByteArray data = f.readAll();
    return fromJson(QString::fromUtf8(data), error);
}

/* ─── parseNode récursif ──────────────────────────────────────────── */
NavigationNode* NavigationTreeParser::parseNode(const QJsonObject& obj, NavigationNode* parent, QString* error)
{
    const QString name = obj.value("name").toString();
    if (name.isEmpty()) {
        jsonError(QObject::tr("Node without 'name'"), error);
        return nullptr;
    }

    bool enabled = obj.value("enabled").toBool(true);

    auto* node = new NavigationNode(name, parent);   // utilise ton ctor
    node->setEnabled(enabled);

    for (const QJsonValue& v :  obj.value("children").toArray()) {
        if (!v.isObject())
            continue;
        NavigationNode* child = parseNode(v.toObject(), node, error);
        if (!child)
            return nullptr;
        node->addChild(child);                       // méthode existante
    }
    return node;
}

/* ─── Helpers privés ──────────────────────────────────────────────── */
QString NavigationTreeParser::jsonError(const QString& msg, QString* out)
{
    if (out)
        *out = msg;
    return {};
}
