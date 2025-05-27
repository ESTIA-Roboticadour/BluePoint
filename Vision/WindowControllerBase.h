#pragma once
#include "ModelBase.h"
#include "WindowBase.h"

#include <QObject>

class WindowControllerBase : public QObject
{
	Q_OBJECT

public:
	explicit WindowControllerBase(ModelBase* model, WindowBase* view, QObject* parent = nullptr);
	virtual ~WindowControllerBase() = default;

protected slots:
	virtual void onViewCloseRequested() = 0;

private:
	void setupConnections();

protected:
	WindowBase* m_view;
	ModelBase* m_model;
};
