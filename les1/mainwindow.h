#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_task1_solve_pushButton_pressed();

    void on_task1_clear_pushButton_pressed();

    void on_task2_solve_pushButton_pressed();

    void on_task2_clear_pushButton_pressed();

    void on_task3_add_pushButton_pressed();

    void on_task3_replace_pushButton_pressed();

    void on_task3_insert_pushButton_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
