#pragma once
#include "ModelBase.h"
#include <QObject>
#include <QWidget>

class WidgetControllerBase : public QObject
{
	Q_OBJECT

public:
	explicit WidgetControllerBase(ModelBase* model, QWidget* view, QObject* parent = nullptr);
	virtual ~WidgetControllerBase() = default;

protected slots:
	virtual void onViewDestroyed() = 0;

private:
	virtual void setupConnections();

private:
	QWidget* m_view;
	ModelBase* m_model;
};

