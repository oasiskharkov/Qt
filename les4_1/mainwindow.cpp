#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>

MainWindow::MainWindow(QApplication& app, QWidget *parent)
    :
      QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , application(app)
    , model(new QFileSystemModel)
    , filePath("")
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
    translator.load(langsPath[Langs::ENG]);
    application.installTranslator(&translator);

    ui->explorer_treeView->setModel(model);
    model->setRootPath(QDir::currentPath());
    model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Drives);
    model->setNameFilters({"*.txt"});
    model->setNameFilterDisables(false);

    for(int i = 1; i < model->columnCount(); ++i)
    {
        ui->explorer_treeView->hideColumn(i);
    }
    ui->explorer_treeView->setHeaderHidden(true);

    connect(this, &MainWindow::TreeViewSelectItem, this, &MainWindow::OnItemSelected);

    ShowCurrentPath();

    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    settingsMenu = new QMenu(this);
    refMenu = new QMenu(this);

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->menuBar()->addMenu(settingsMenu);
    this->menuBar()->addMenu(refMenu);

    newAction = fileMenu->addAction("", this, SLOT(NewFile()), Qt::CTRL + Qt::Key_N);
    openAction = fileMenu->addAction("", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    readOnlyAction = fileMenu->addAction("", this, SLOT(ReadOnlyFile()), Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    saveAction = fileMenu->addAction("", this, SLOT(SaveFile()), Qt::CTRL + Qt::Key_S);
    saveAsAction = fileMenu->addAction("", this, SLOT(SaveFileAs()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    closeAction = fileMenu->addAction("", this, SLOT(CloseFile()), Qt::CTRL + Qt::SHIFT + Qt::Key_C);
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction("", this, SLOT(Exit()), Qt::ALT + Qt::Key_F4);

    cutAction = editMenu->addAction("", this, SLOT(Cut()), Qt::CTRL + Qt::Key_X);
    copyAction = editMenu->addAction("", this, SLOT(Copy()), Qt::CTRL + Qt::Key_C);
    pasteAction = editMenu->addAction("", this, SLOT(Paste()), Qt::CTRL + Qt::Key_V);
    deleteAction = editMenu->addAction("", this, SLOT(Delete()), Qt::CTRL + Qt::Key_D);
    editMenu->addSeparator();
    clearAction = editMenu->addAction("", this, SLOT(Clear()), Qt::CTRL + Qt::Key_K);

    langSubMenu = new QMenu(settingsMenu);
    settingsMenu->addMenu(langSubMenu);

    engCheckable = langSubMenu->addAction("", this, SLOT(CheckEnglish()));
    engCheckable->setCheckable(true);
    engCheckable->setChecked(true);

    rusCheckable = langSubMenu->addAction("", this, SLOT(CheckRussian()));
    rusCheckable->setCheckable(true);
    rusCheckable->setChecked(false);

    shortcutSubMenu = new QMenu(settingsMenu);
    settingsMenu->addMenu(shortcutSubMenu);

    f2Checkable = shortcutSubMenu->addAction("", this, SLOT(F2()));
    f2Checkable->setCheckable(true);
    f2Checkable->setChecked(false);

    f3Checkable = shortcutSubMenu->addAction("", this, SLOT(F3()));
    f3Checkable->setCheckable(true);
    f3Checkable->setChecked(false);

    f4Checkable = shortcutSubMenu->addAction("", this, SLOT(F4()));
    f4Checkable->setCheckable(true);
    f4Checkable->setChecked(false);

    f5Checkable = shortcutSubMenu->addAction("", this, SLOT(F5()));
    f5Checkable->setCheckable(true);
    f5Checkable->setChecked(false);

    f6Checkable = shortcutSubMenu->addAction("", this, SLOT(F6()));
    f6Checkable->setCheckable(true);
    f6Checkable->setChecked(false);

    f7Checkable = shortcutSubMenu->addAction("", this, SLOT(F7()));
    f7Checkable->setCheckable(true);
    f7Checkable->setChecked(false);

    themeSubMenu = new QMenu(settingsMenu);
    settingsMenu->addMenu(themeSubMenu);

    lightCheckable = themeSubMenu->addAction("", this, SLOT(SetLightTheme()));
    lightCheckable->setCheckable(true);
    lightCheckable->setChecked(true);

    darkCheckable = themeSubMenu->addAction("", this, SLOT(SetDarkTheme()));
    darkCheckable->setCheckable(true);
    darkCheckable->setChecked(false);

    aboutAction = refMenu->addAction("", this, SLOT(About()), Qt::Key_F12);
    refMenu->addSeparator();
    helpAction = refMenu->addAction("", this, SLOT(Help()), Qt::Key_F1);

    aboutForm = new AboutForm(this);
    helpForm = new HelpForm(this);

    QFile file(":/dark_style");
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file);
        darkStyle = stream.readAll();
        file.close();
    }

    RetranslateUi(Langs::ENG);
}

void MainWindow::NewFile()
{
    ui->textEdit->setReadOnly(false);
    ui->textEdit->clear();
    filePath = "";
}

void MainWindow::OpenFileFunc()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File", QDir::current().path(), filter);
    if (path.length() > 0)
    {
        int index = path.indexOf(".txt");
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && path.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                filePath = path;
                file.close();
            }
        }
    }
}

void MainWindow::RetranslateUi(Langs lang)
{
    setWindowTitle(tr("Text Editor 2.0"));
    filter = trUtf8("Text File(*.txt);;All Files(*.*)");

    fileMenu->setTitle(tr("&File"));
    editMenu->setTitle(tr("&Edit"));
    settingsMenu->setTitle(tr("&Settings"));
    refMenu->setTitle(tr("&Reference"));

    newAction->setText(tr("&New"));
    openAction->setText(tr("&Open"));
    readOnlyAction->setText(tr("&Read Only"));
    saveAction->setText(tr("&Save"));
    saveAsAction->setText(tr("&Save As"));
    closeAction->setText(tr("&Close"));
    exitAction->setText(tr("&Exit"));

    cutAction->setText(tr("&Cut"));
    copyAction->setText(tr("&Copy"));
    pasteAction->setText(tr("&Paste"));
    deleteAction->setText(tr("&Delete"));
    clearAction->setText(tr("&Clear"));

    langSubMenu->setTitle(tr("&Language"));

    engCheckable->setText(tr("&English"));
    rusCheckable->setText(tr("&Russian"));

    shortcutSubMenu->setTitle(tr("&Shortcuts"));
    f2Checkable->setText(tr("&New -> F2"));
    f3Checkable->setText(tr("&Open -> F3"));;
    f4Checkable->setText(tr("&Read Only -> F4"));
    f5Checkable->setText(tr("&Save -> F5"));
    f6Checkable->setText(tr("&Save As -> F6"));
    f7Checkable->setText(tr("&Close -> F7"));

    themeSubMenu->setTitle(tr("&Theme"));
    lightCheckable->setText(tr("&Light"));
    darkCheckable->setText(tr("&Dark"));

    aboutAction->setText(tr("&About"));
    helpAction->setText(tr("&Help"));

    aboutForm->RetranslateUi(lang);
    helpForm->RetranslateUi(lang);
}

void MainWindow::SetTheme(Theme theme)
{
    switch (theme)
    {
    case Theme::LIGHT:
        application.setStyleSheet("");
        break;
    case Theme::DARK:
        application.setStyleSheet(darkStyle);
        break;
    }
    aboutForm->SetTheme(theme);
    helpForm->SetTheme(theme);
}

void MainWindow::ShowCurrentPath()
{
    QStringList parts  = QDir::currentPath().split("/");
    if(parts.size())
    {
        for (int i = 0; i < parts.size(); ++i)
        {
            QString currentPath;
            for (int j = 0; j <= i; ++j)
            {
                currentPath.append(parts.at(j)).append("/");
            }
            ui->explorer_treeView->expand(model->index(currentPath));
        }
    }
}

void MainWindow::OpenFile()
{
    OpenFileFunc();
    ui->textEdit->setReadOnly(false);
}

void MainWindow::ReadOnlyFile()
{
    OpenFileFunc();
    ui->textEdit->setReadOnly(true);
}

void MainWindow::SaveFile()
{

}

void MainWindow::SaveFileAs()
{

}

void MainWindow::CloseFile()
{
    ui->textEdit->clear();
    ui->textEdit->setReadOnly(false);
    filePath = "";
}

void MainWindow::Exit()
{
    this->close();
}

void MainWindow::Cut()
{

}

void MainWindow::Copy()
{

}

void MainWindow::Paste()
{

}

void MainWindow::Delete()
{

}

void MainWindow::Clear()
{
    ui->textEdit->clear();
}

void MainWindow::CheckEnglish()
{
    if(engCheckable->isChecked())
    {
        rusCheckable->setChecked(false);
        translator.load(langsPath[Langs::ENG]);
        RetranslateUi(Langs::ENG);
    }
    else
    {
        rusCheckable->setChecked(true);
    }
}

void MainWindow::CheckRussian()
{
    if(rusCheckable->isChecked())
    {
        engCheckable->setChecked(false);
        translator.load(langsPath[Langs::RUS]);
        RetranslateUi(Langs::RUS);
    }
    else
    {
        engCheckable->setChecked(true);
    }
}

void MainWindow::About()
{
    aboutForm->show();
}

void MainWindow::Help()
{
    helpForm->show();
}

void MainWindow::F2()
{
    if(f2Checkable->isChecked())
    {
        newAction->setShortcut(Qt::Key_F2);
    }
    else
    {
        newAction->setShortcut(Qt::CTRL + Qt::Key_N);
    }
}

void MainWindow::F3()
{
    if(f3Checkable->isChecked())
    {
        openAction->setShortcut(Qt::Key_F3);
    }
    else
    {
        openAction->setShortcut(Qt::CTRL + Qt::Key_O);
    }
}

void MainWindow::F4()
{
    if(f4Checkable->isChecked())
    {
        readOnlyAction->setShortcut(Qt::Key_F4);
    }
    else
    {
        readOnlyAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    }
}

void MainWindow::F5()
{
    if(f5Checkable->isChecked())
    {
        saveAction->setShortcut(Qt::Key_F5);
    }
    else
    {
        saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    }
}

void MainWindow::F6()
{
    if(f6Checkable->isChecked())
    {
        saveAsAction->setShortcut(Qt::Key_F6);
    }
    else
    {
        saveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    }
}

void MainWindow::F7()
{
    if(f7Checkable->isChecked())
    {
        closeAction->setShortcut(Qt::Key_F7);
    }
    else
    {
        closeAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_C);
    }
}

void MainWindow::SetLightTheme()
{
    if(lightCheckable->isChecked())
    {
        darkCheckable->setChecked(false);
        SetTheme(Theme::LIGHT);
    }
    else
    {
        darkCheckable->setChecked(true);
    }
}

void MainWindow::SetDarkTheme()
{
    if(darkCheckable->isChecked())
    {
        lightCheckable->setChecked(false);
        SetTheme(Theme::DARK);
    }
    else
    {
        lightCheckable->setChecked(true);
    }
}

void MainWindow::on_explorer_treeView_clicked(const QModelIndex &index)
{
    QString filePath = model->filePath(index);
    ui->path_lineEdit->setText(filePath);
    emit TreeViewSelectItem(filePath);
}

void MainWindow::OnItemSelected(const QString& path)
{
    if (path.length() > 0)
    {
        int index = path.indexOf(".txt");
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && path.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                filePath = path;
                file.close();
            }
        }
    }
}

