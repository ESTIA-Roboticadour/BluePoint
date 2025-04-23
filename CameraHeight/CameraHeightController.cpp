#include "CameraHeightController.h"

CameraHeightController::CameraHeightController(CameraHeightWindow* view, CameraHeightModel* model, QObject* parent) :
	QObject(parent),
	m_view(view),
	m_model(model)
{
	connect(m_view, &CameraHeightWindow::closing, this, &CameraHeightController::onViewClosing);
	connect(m_view, &CameraHeightWindow::fovLabelTextChanged, this, &CameraHeightController::onViewFovTextChanged);
	connect(m_view, &CameraHeightWindow::widthLabelTextChanged, this, &CameraHeightController::onViewWidthTextChanged);

	connect(m_model, &CameraHeightModel::errorThrowed, m_view, &CameraHeightWindow::onErrorThrowed);
	connect(m_model, &CameraHeightModel::fovChanged, this, &CameraHeightController::onModelFovChanged);
	connect(m_model, &CameraHeightModel::widthChanged, this, &CameraHeightController::onModelWidthChanged);
	connect(m_model, &CameraHeightModel::heightChanged, this, &CameraHeightController::onModelHeightChanged);
}

CameraHeightController::~CameraHeightController()
{
	delete m_model;
	delete m_view;
}

void CameraHeightController::onViewClosing()
{
	deleteLater();
}

void CameraHeightController::onViewFovTextChanged(const QString& text)
{
	bool ok;
	float value = text.toFloat(&ok);
	if (ok && value > 0)
	{
		m_model->setFov(value);
	}
	else
	{
		m_view->onErrorThrowed("Bad input", "Input value is not a positive number.");
	}
}

void CameraHeightController::onViewWidthTextChanged(const QString& text)
{
	bool ok;
	float value = text.toFloat(&ok);
	if (ok && value > 0)
	{
		m_model->setWidth(value);
	}
	else
	{
		m_view->onErrorThrowed("Bad input", "Input value is not a positive number.");
	}
}

void CameraHeightController::onModelFovChanged(float fov)
{
	//m_view->setFovText(QString::number(fov, 'f', 3));
	m_view->setFovText(QString::number(fov));
}

void CameraHeightController::onModelWidthChanged(float width)
{
	//m_view->setWidthText(QString::number(width, 'f', 3));
	m_view->setWidthText(QString::number(width));
}

void CameraHeightController::onModelHeightChanged(float height)
{
	m_view->setHeightText(QString::number(height, 'f', 3));
}
