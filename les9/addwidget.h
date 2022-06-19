#ifndef ADDWIDGET_H
#define ADDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QQuickWidget>
#include <QDateTime>

class AddWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddWidget(QWidget *parent = nullptr);
private:
    void Init();
signals:
private:
    QQuickWidget* qw;
};

#endif // ADDWIDGET_H
