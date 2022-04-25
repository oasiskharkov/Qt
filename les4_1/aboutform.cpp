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

void AboutForm::RetranslateUi(Langs lang)
{
    setWindowTitle(tr("About"));

    switch(lang)
    {
    case Langs::ENG:
        ui->about_label->setText(text_eng);
        break;
    case Langs::RUS:
        ui->about_label->setText(text_rus);
        break;
    }
}

void AboutForm::Init()
{
    this->setWindowFlags(Qt::Dialog);

    QString path = ":/about_";
    QFile file_eng(path + "eng");
    if (file_eng.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file_eng);
        text_eng = stream.readAll();
        file_eng.close();
    }

    QFile file_rus(path + "rus");
    if (file_rus.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file_rus);
        text_rus = stream.readAll();
        file_rus.close();
    }

    RetranslateUi(Langs::ENG);
}
