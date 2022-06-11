#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets>

#include "aboutform.h"
#include "helpform.h"
#include "filefinderform.h"

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
    void PrintFile();
    void CloseFile();
    void FindFile();
    void Exit();
    void Cut();
    void Copy();
    void Paste();
    void Delete();
    void SelectAll();
    void Clear();
    void InsertDate();
    void InsertTime();
    void AlignLeft();
    void AlignCenter();
    void AlignRight();
    void CopyFormat();
    void ApplyFormat();
    void ResetFormat();
    void CheckEnglish();
    void CheckRussian();
    void F2();
    void F3();
    void F4();
    void F5();
    void F6();
    void F7();
    void SetLightTheme();
    void SetDarkTheme();
    void ChangeFont();
    void ShowExplorer();
    void About();
    void Help();
    void TreeViewItemClicked(const QModelIndex &index);
    void OnItemSelected(const QString& path);
    void OnTextChanged();
    void OpenFoundFile(const QString& path);
signals:
    void TreeViewSelectItem(const QString& path);
private:
    void Init();
    void OpenFileFunc();
    void RetranslateUi(Langs lang);
    void SetTheme(Theme theme);
    void ShowCurrentPath(const QString& path);
    void Align(Qt::Alignment alignment);
    void InsertDateTime(const QString& format);
private:
    Ui::MainWindow *ui;
    QApplication& application;
    QTranslator translator;
    QFileSystemModel* model;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* settingsMenu;
    QMenu* viewMenu;
    QMenu* refMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* readOnlyAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;
    QAction* findFileAction;
    QAction* printAction;
    QAction* exitAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* deleteAction;
    QAction* selectAllAction;
    QAction* clearAction;
    QAction* insertDateAction;
    QAction* insertTimeAction;
    QMenu* alignSubMenu;
    QAction* alignCenterAction;
    QAction* alignLeftAction;
    QAction* alignRightAction;
    QMenu* formatSubMenu;
    QAction* copyFormatAction;
    QAction* applyFormatAction;
    QAction* resetFormatAction;
    QMenu* langSubMenu;
    QAction* engCheckable;
    QAction* rusCheckable;
    QMenu* shortcutSubMenu;
    QAction* f2Checkable;
    QAction* f3Checkable;
    QAction* f4Checkable;
    QAction* f5Checkable;
    QAction* f6Checkable;
    QAction* f7Checkable;
    QMenu* themeSubMenu;
    QAction* darkCheckable;
    QAction* lightCheckable;
    QAction* fontAction;
    QAction* explorerCheckable;
    QAction* aboutAction;
    QAction* helpAction;

    QLabel* fileInfoLabel;

    AboutForm* aboutForm;
    HelpForm* helpForm;
    FileFinderForm* fileFinderForm;

    QString filePath;
    QString filter;
    QPair<QFont, Qt::Alignment> format;
    bool formatCopied = false;
};
#endif // MAINWINDOW_H
