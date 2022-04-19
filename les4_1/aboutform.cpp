#include "aboutform.h"
#include "ui_aboutform.h"
#include <QFile>
#include <QTextStream>

AboutForm::AboutForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutForm)
{
    ui->setupUi(this);
    Init();
}

AboutForm::~AboutForm()
{
    delete ui;
}

void AboutForm::Init()
{
    this->setWindowFlags(Qt::Dialog);
    this->setWindowTitle(tr("About"));

    QFile file(":/about");
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file);
        ui->about_label->setText(stream.readAll());
    }
}
