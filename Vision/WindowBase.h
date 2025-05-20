#pragma once
#include <QtWidgets/QMainWindow>
#include <QCloseEvent>

class WindowBase : public QMainWindow
{
	Q_OBJECT

public:
	explicit WindowBase(QWidget* parent = nullptr);
	virtual ~WindowBase() = default;

protected:
	void closeEvent(QCloseEvent* event) override;

signals:
	void closeRequested();
};
