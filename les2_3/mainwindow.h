#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>

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
    void on_paint_pushButton_pressed();
    void on_clear_pushButton_pressed();

private:
    void Init();

private:
    Ui::MainWindow *ui;
    QStandardItemModel model;
};
#endif // MAINWINDOW_H
