#pragma once
#include "CameraHeightModel.h"
#include "CameraHeightWindow.h"

#include <QObject>
#include <QString>

class CameraHeightController : public QObject
{
	Q_OBJECT

public:
	CameraHeightController(CameraHeightWindow* view, CameraHeightModel* model, QObject* parent = nullptr);
	~CameraHeightController();

public slots:
	void onViewClosing();
	void onViewFovTextChanged(const QString& text);
	void onViewWidthTextChanged(const QString& text);

	void onModelFovChanged(float fov);
	void onModelWidthChanged(float width);
	void onModelHeightChanged(float height);

private:
	CameraHeightModel*  m_model;
	CameraHeightWindow* m_view;
};
