#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clear_pushButton_pressed()
{
    ui->value_lineEdit->clear();
}

void MainWindow::on_value_lineEdit_textEdited(const QString& line)
{
    auto replacement = replacer.GetReplacement(line.toUpper());
    if(replacement.has_value())
    {
        ui->value_lineEdit->setText(replacer.Replace(line, replacement.value()));
    }
}

