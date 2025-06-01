#pragma once
#include <QString>
#include <QWidget>

class Helper
{
public:
	static QString getSaveConfigFile(QWidget* parent,
		const QString& defaultFileName = {},
		const QString& defaultDir = {},
		const QString& filters = QObject::tr("Configuration files (*.json);;All files (*.*)"));

	static QString getOpenConfigFile(
		QWidget* parent,
		const QString& defaultDir = {},
		const QString& filters = QObject::tr("Configuration files (*.json);;All files (*.*)"));
};
