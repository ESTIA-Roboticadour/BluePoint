#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include "LogTool_global.h"

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QPoint>

#include "LogModel.h"

class LOGTOOL_API LogWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor debugColor    READ debugColor    WRITE setDebugColor    DESIGNABLE true)
    Q_PROPERTY(QColor infoColor     READ infoColor     WRITE setInfoColor     DESIGNABLE true)
    Q_PROPERTY(QColor warningColor  READ warningColor  WRITE setWarningColor  DESIGNABLE true)
    Q_PROPERTY(QColor criticalColor READ criticalColor WRITE setCriticalColor DESIGNABLE true)
    Q_PROPERTY(QColor fatalColor    READ fatalColor    WRITE setFatalColor    DESIGNABLE true)
public:
    explicit LogWidget(QWidget* parent = nullptr);

    QColor debugColor()    const;
    QColor infoColor()     const;
    QColor warningColor()  const;
    QColor criticalColor() const;
    QColor fatalColor()    const;

    void setDebugColor   (const QColor&);
    void setInfoColor    (const QColor&);
    void setWarningColor (const QColor&);
    void setCriticalColor(const QColor&);
    void setFatalColor   (const QColor&);

private slots:
    void copySelectedRow();
    void showContextMenu(const QPoint&);

private:
    QTableView* m_view{ nullptr };
    LogModel* m_model{ nullptr };
};

#endif // LOGWIDGET_H
