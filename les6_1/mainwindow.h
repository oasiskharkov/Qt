#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMdiArea;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void Init();

private slots:
    void NewFile();
    void OpenFile();
    void SaveFile();
    void Exit();
private:
    Ui::MainWindow *ui;
    QMenu* fileMenu;
    QAction* newFile;
    QAction* openFile;
    QAction* saveFile;
    QAction* exit;
    QMdiArea* area;
    QString filter;

};
#endif // MAINWINDOW_H
