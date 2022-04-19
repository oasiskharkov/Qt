#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets>

#include "aboutform.h"
#include "helpform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QTranslator& translator, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void NewFile();
    void OpenFile();
    void ReadOnlyFile();
    void SaveFile();
    void SaveFileAs();
    void CloseFile();
    void Exit();
    void Cut();
    void Copy();
    void Paste();
    void Delete();
    void Clear();
    void CheckEnglish();
    void CheckRussian();
    void About();
    void Help();

private:
    void Init();
    void OpenFileFunc();

private:
    Ui::MainWindow *ui;
    QAction* engCheckable;
    QAction* rusCheckable;
    AboutForm* aboutForm;
    HelpForm* helpForm;
    QString filePath;
    QString filter;
    QTranslator& translator;
};
#endif // MAINWINDOW_H
