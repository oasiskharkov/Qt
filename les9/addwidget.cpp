#include "addwidget.h"

AddWidget::AddWidget(QWidget *parent) : QWidget(parent)
{
    Init();
}

void AddWidget::Init()
{
    qw = new QQuickWidget{QUrl{"qrc:/add.qml"}};
}
