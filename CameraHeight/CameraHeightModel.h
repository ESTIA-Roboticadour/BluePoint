#pragma once
#include <QObject>
#include <QString>

class CameraHeightModel : public QObject
{
	Q_OBJECT

public:
	CameraHeightModel(QObject* parent = nullptr);
	CameraHeightModel(float fov, float width, QObject* parent = nullptr);
	~CameraHeightModel() = default;

public slots:
	void setFov(float fov);
	void setWidth(float width);

public:
	float getFov() const;
	float getWidth() const;
	float getHeight() const;

private:
	void computeHeight();
	void setHeight(float height);

signals:
	void fovChanged(float fov);
	void widthChanged(float width);
	void heightChanged(float height);
	void errorThrowed(const QString& error, const QString& errorMessage);

private:
	float m_fov;
	float m_width;
	float m_height;
};
