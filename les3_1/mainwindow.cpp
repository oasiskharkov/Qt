#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpform.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      openedFileName("")
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    filter = trUtf8("Text File(*.txt)");

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);
}

void MainWindow::ExtendedFileSave()
{
    if(!ui->textEdit->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton reply;
        QString type = openedFileName.isEmpty() ? " as" : "";
        reply = QMessageBox::question(this, "Save file" + type, "Do you want to save file" + type + "?", QMessageBox::Yes | QMessageBox::No);
        if (QMessageBox::Yes == reply)
        {
            if (!openedFileName.isEmpty())
            {
                FileSave();
            }
            else
            {
                FileSaveAs();
            }
        }
    }
}

void MainWindow::FileSave()
{
    QString s = QFileDialog::getSaveFileName(this, "Save File", openedFileName, filter);
    if (s.length() > 0)
    {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(s);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
                openedFileName = s;
            }
        }
    }
}

void MainWindow::FileSaveAs()
{
    QString s = QFileDialog::getSaveFileName(this, "Save File As", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(s);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
                openedFileName = s;
            }
        }
    }
}

void MainWindow::FileOpen()
{
    QString s = QFileDialog::getOpenFileName(this, "Open File", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && s.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                openedFileName = s;
                file.close();
            }
        }
    }
}

void MainWindow::on_new_pushButton_pressed()
{
    ExtendedFileSave();

    ui->textEdit->setReadOnly(false);
    ui->textEdit->setDisabled(false);
    ui->textEdit->clear();
    openedFileName = "";
}

void MainWindow::on_close_pushButton_pressed()
{
    ExtendedFileSave();

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);
    ui->textEdit->clear();
    openedFileName = "";
}

void MainWindow::on_open_pushButton_pressed()
{
    ExtendedFileSave();

    FileOpen();

    ui->textEdit->setReadOnly(false);
    ui->textEdit->setDisabled(false);
}

void MainWindow::on_save_pushButton_pressed()
{
    FileSave();
}

void MainWindow::on_saveas_pushButton_pressed()
{
    FileSaveAs();
}

void MainWindow::on_help_pushButton_pressed()
{
    HelpForm* help = new HelpForm(this);
    if(help)
    {
        help->show();
    }
}

