#pragma once
#include <QObject>

class ModelBase : public QObject
{
	Q_OBJECT

public:
	explicit ModelBase(QObject* parent = nullptr);
	virtual ~ModelBase() = default;

	bool isReleased() const;
	virtual void release();

signals:
	void released();

private:
	bool m_isRelease;
};
