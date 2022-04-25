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
    MainWindow(QApplication& app, QWidget* parent = nullptr);
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
    void RetranslateUi(Langs lang);

private:
    Ui::MainWindow *ui;
    QApplication& application;
    QTranslator translator;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* viewMenu;
    QMenu* refMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* readOnlyAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;
    QAction* exitAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* deleteAction;
    QAction* clearAction;
    QAction* engCheckable;
    QAction* rusCheckable;
    QMenu* langSubMenu;
    QAction* aboutAction;
    QAction* helpAction;

    AboutForm* aboutForm;
    HelpForm* helpForm;

    QString filePath;
    QString filter;

};
#endif // MAINWINDOW_H
