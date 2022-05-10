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

void HelpForm::RetranslateUi(Langs lang)
{
    setWindowTitle(tr("Help"));

    switch(lang)
    {
    case Langs::ENG:
        ui->help_label->setText(text_eng);
        break;
    case Langs::RUS:
        ui->help_label->setText(text_rus);
        break;
    }
}

void HelpForm::SetTheme(Theme theme)
{
    switch (theme)
    {
    case Theme::LIGHT:
        setStyleSheet("");
        break;
    case Theme::DARK:
        setStyleSheet(darkStyle);
        break;
    }
}

void HelpForm::Init()
{
    this->setWindowFlags(Qt::Dialog);

    QString path = ":/help_";
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
