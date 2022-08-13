#include "addform.h"
#include "ui_addform.h"
#include <QMessageBox>
#include <QRegExp>

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
    ui->priority_comboBox->addItems(QStringList{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});
    reset_values();
}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::on_clear_pushButton_clicked()
{
    reset_values();
}


void AddForm::on_add_pushButton_clicked()
{
    if(ui->task_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Empty task", "Write task, please!");
        return;
    }

    if(!checkDate(ui->dateEdit->date().toString("dd.MM.yyyy")))
    {
        QMessageBox::warning(this, "Incorrect Date", "Input correct date, please!");
        return;
    }

    emit add_entry(QStringList{ui->task_lineEdit->text(), ui->dateEdit->date().toString("dd.MM.yyyy"), ui->priority_comboBox->currentText()});
    this->close();
}

void AddForm::reset_values()
{
    ui->task_lineEdit->clear();
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    ui->priority_comboBox->setCurrentIndex(0);
}

bool AddForm::checkDate(const QString& date) const
{
    QRegExp rx("(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[012])[-/.](19\\d{2}|20\\d{2})");
    return rx.exactMatch(date);
}


