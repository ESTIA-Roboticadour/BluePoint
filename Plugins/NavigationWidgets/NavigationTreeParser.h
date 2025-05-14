#ifndef NAVIGATIONTREEPARSER_H
#define NAVIGATIONTREEPARSER_H

#include "NavigationWidgets_global.h"
#include "NavigationNode.h"
#include "NavigationTree.h"

#include <memory>
#include <QString>
#include <QStringView>

class NAVIGATIONWIDGETS_API NavigationTreeParser
{
    Q_GADGET                      // pas indispensable, mais garde la finition Qt

public:
    /* Parse un JSON « inline » (QString, QStringView, QByteArray) */
    static std::unique_ptr<NavigationTree> fromJson(QStringView json, QString* error = nullptr);

    /* Parse un fichier (chemin classique ou ressource Qt) */
    static std::unique_ptr<NavigationTree> fromFile(const QString& filePath, QString* error = nullptr);

private:                                        // helpers internes
    /* ─── parseNode récursif ──────────────────────────────────────────── */
    static NavigationNode* parseNode(const QJsonObject& obj, NavigationNode* parent, QString* error);

    static QString jsonError(const QString& msg, QString* out);
};

#endif // NAVIGATIONTREEPARSER_H
