#pragma once

#include "ui_CameraWindow.h"
#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include <QString>
#include <QSize>

QT_BEGIN_NAMESPACE
namespace Ui { class CameraWindowClass; };
QT_END_NAMESPACE

class CameraWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit CameraWindow(QWidget* parent = nullptr);
	~CameraWindow();

	void setDimensionsLabel(const QString& dimensions);
	void setFpsLabel(const QString& fps);
	void setFrameLabel(const QImage& image);

	void log(const QString& message);
	void logError(const QString& error, const QString& errorMessage);

	QString getVideoFilename() const;
	QSize getFrameLabelSize() const;

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	void resetUi();
	void setupShortcuts();
	void internalSetFrame(const QImage& image);
	
	static QImage resizeFrame(const QImage& image);
	static QString formatTime(int seconds);

public slots:
	void onRecordingStarted(const QString& filename);
	void onRecordingStopped();
	void onDeviceConnected();
	void onDeviceDisconnected();
	void onRecordingTimeChanged(int seconds);
	void onCurrentFpsChanged(float fps);

private slots:
	void onStartOrStopAction();

signals:
	void closing();
	void openButtonClicked();
	void closeButtonClicked();
	void startButtonClicked();
	void stopButtonClicked();
	void deviceChanged(int deviceIndex);

private:
	Ui::CameraWindowClass *m_ui;
};
