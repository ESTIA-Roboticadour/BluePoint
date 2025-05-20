#pragma once
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

class LogoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogoWidget(QWidget* parent = nullptr);
    ~LogoWidget() = default;

    void setSize(int targetSize, Qt::TransformationMode mode = Qt::SmoothTransformation);
    void setSize(int width, int height, Qt::TransformationMode mode = Qt::SmoothTransformation);

private:
	QLabel* logoLabel;
};
