#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "addform.h"

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
    void on_add_pushButton_clicked();
    void on_remove_pushButton_clicked();
    void on_clear_pushButton_clicked();
    void on_close_pushButton_clicked();

public slots:
    void on_add_enrty(const QStringList& entry);

private:
    Ui::MainWindow *ui;
    AddForm* addForm;
    QSqlTableModel model;
    QSqlDatabase db;
    QString addEntry;
    QString removeAll;
    QString dropTable;
    QString maxId;
    int id;
};
#endif // MAINWINDOW_H
