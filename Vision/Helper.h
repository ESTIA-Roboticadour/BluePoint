#pragma once
#include <QString>
#include <QWidget>

class Helper
{
public:
    static QString getSaveConfigFile(QWidget* parent,
        const QString& defaultFileName = {},
        const QString& defaultDir = {},
        const QString& filters = "Configuration files (*.json)");
};
