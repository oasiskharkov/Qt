#include "helpform.h"
#include "ui_helpform.h"
#include <QFile>
#include <QTextStream>

HelpForm::HelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpForm)
{
    ui->setupUi(this);
    Init();
}

HelpForm::~HelpForm()
{
    delete ui;
}

void HelpForm::Init()
{
    this->setWindowFlags(Qt::Dialog);
    this->setWindowTitle(tr("Help"));

    QFile file(":/help");
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file);
        ui->help_label->setText(stream.readAll());
    }
}
