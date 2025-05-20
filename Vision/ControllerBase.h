#pragma once
#include "ModelBase.h"
#include "ViewBase.h"

#include <QObject>

class ControllerBase : public QObject
{
	Q_OBJECT

	enum CloseBehavior {
		DestroyModelThenView,
		DestroyViewOnly
	};

public:
	explicit ControllerBase(ModelBase* model, ViewBase* view, CloseBehavior closeBehaviour = CloseBehavior::DestroyModelThenView, QObject* parent = nullptr);
	~ControllerBase() {}

private slots:
	void onModelReleased();
	void onModelDestroyed();

private:
	ModelBase* m_model;
	ViewBase* m_view;
};
