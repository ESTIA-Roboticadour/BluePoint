#pragma once
#include <QObject>

class IRobot : public QObject
{
    Q_OBJECT

public:
	explicit IRobot(QObject* parent = nullptr) : QObject(parent) {}
	virtual void controlLoop() = 0;
};
