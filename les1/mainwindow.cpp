#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>

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

void MainWindow::on_task1_solve_pushButton_pressed()
{
    bool nonError = true;
    QString error = "Incorrect value";

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::red);

    qreal a = ui->task1_a_lineEdit->text().toDouble(&nonError);
    if(!nonError)
    {
        ui->task1_a_lineEdit->setText(error);
        ui->task1_a_lineEdit->setPalette(palette);
        ui->task1_result_lineEdit->clear();
        return;
    }

    qreal b = ui->task1_b_lineEdit->text().toDouble(&nonError);
    if(!nonError)
    {
        ui->task1_b_lineEdit->setText(error);
        ui->task1_b_lineEdit->setPalette(palette);
        ui->task1_result_lineEdit->clear();
        return;
    }

    qreal c = ui->task1_c_lineEdit->text().toDouble(&nonError);
    if(!nonError)
    {
        ui->task1_c_lineEdit->setText(error);
        ui->task1_c_lineEdit->setPalette(palette);
        ui->task1_result_lineEdit->clear();
        return;
    }

    qreal disc = b * b - 4 * a * c;

    QString answer;
    if(disc < 0.0)
    {
        answer = "No solution";
    }
    else if(qFuzzyIsNull(disc))
    {
        if(!qFuzzyIsNull(a))
        {
            qreal x = -b / (2 * a);
            answer = "x=" + QString::number(x);
        }
        else
        {
            answer = "No solution";
        }

    }
    else
    {
        if(!qFuzzyIsNull(a))
        {
            qreal x1 = (-b + sqrt(disc)) / (2 * a);
            qreal x2 = (-b - sqrt(disc)) / (2 * a);
            answer = "x1=" + QString::number(x1) + " x2=" + QString::number(x2);
        }
        else
        {
            qreal x = -c/b;
            answer = "x1=" + QString::number(x);
        }
    }
    ui->task1_result_lineEdit->setText(answer);
}

void MainWindow::on_task1_clear_pushButton_pressed()
{
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);

    ui->task1_a_lineEdit->clear();
    ui->task1_a_lineEdit->setPalette(palette);
    ui->task1_b_lineEdit->clear();
    ui->task1_b_lineEdit->setPalette(palette);
    ui->task1_c_lineEdit->clear();
    ui->task1_c_lineEdit->setPalette(palette);
    ui->task1_result_lineEdit->clear();
}

void MainWindow::on_task2_solve_pushButton_pressed()
{
    bool nonError = true;
    QString error = "Incorrect value";

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::red);

    qreal a = ui->task2_a_lineEdit->text().toDouble(&nonError);
    if(!nonError || qFuzzyIsNull(a) || a < 0.0)
    {
        ui->task2_a_lineEdit->setText(error);
        ui->task2_a_lineEdit->setPalette(palette);
        ui->task2_c_lineEdit->clear();
        return;
    }

    qreal b = ui->task2_b_lineEdit->text().toDouble(&nonError);
    if(!nonError || qFuzzyIsNull(b) || b < 0.0)
    {
        ui->task2_b_lineEdit->setText(error);
        ui->task2_b_lineEdit->setPalette(palette);
        ui->task2_c_lineEdit->clear();
        return;
    }

    qreal gamma = ui->task2_gamma_lineEdit->text().toDouble(&nonError);
    if(nonError && ui->task2_deg_radioButton->isChecked())
    {
        gamma = qDegreesToRadians(gamma);
    }

    if(!nonError || gamma > M_PI || qFuzzyCompare(gamma, M_PI))
    {
        ui->task2_gamma_lineEdit->setText(error);
        ui->task2_gamma_lineEdit->setPalette(palette);
        ui->task2_c_lineEdit->clear();
        return;
    }

    QString answer;
    qreal c = a * a + b * b - 2 * a * b * qCos(gamma);

    if(c < 0.0)
    {
        answer = "No solution";
    }
    else
    {
        answer = QString::number(sqrt(c));
    }
    ui->task2_c_lineEdit->setText(answer);
}

void MainWindow::on_task2_clear_pushButton_pressed()
{
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);

    ui->task2_a_lineEdit->clear();
    ui->task2_a_lineEdit->setPalette(palette);
    ui->task2_b_lineEdit->clear();
    ui->task2_b_lineEdit->setPalette(palette);
    ui->task2_gamma_lineEdit->clear();
    ui->task2_gamma_lineEdit->setPalette(palette);
    ui->task2_c_lineEdit->clear();
}

void MainWindow::on_task3_add_pushButton_pressed()
{
    QString text = ui->task3_textEdit->toPlainText();
    ui->task3_plainTextEdit->moveCursor(QTextCursor::End);
    ui->task3_plainTextEdit->insertPlainText(text);
    ui->task3_plainTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_task3_replace_pushButton_pressed()
{
    QString text = ui->task3_textEdit->toPlainText();
    ui->task3_plainTextEdit->clear();
    ui->task3_plainTextEdit->insertPlainText(text);
}

void MainWindow::on_task3_insert_pushButton_pressed()
{
    ui->task3_textEdit->clear();
    QString htmlText = "<font color='red'>Hello Geekbrains</font>";
    ui->task3_textEdit->setHtml(htmlText);
}







