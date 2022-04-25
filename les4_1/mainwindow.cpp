#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>

MainWindow::MainWindow(QApplication& app, QWidget *parent)
    :
      QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , application(app)
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

    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    viewMenu = new QMenu(this);
    refMenu = new QMenu(this);

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->menuBar()->addMenu(viewMenu);
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

    langSubMenu = new QMenu(viewMenu);
    viewMenu->addMenu(langSubMenu);

    engCheckable = langSubMenu->addAction("", this, SLOT(CheckEnglish()));
    engCheckable->setCheckable(true);
    engCheckable->setChecked(true);

    rusCheckable = langSubMenu->addAction("", this, SLOT(CheckRussian()));
    rusCheckable->setCheckable(true);
    rusCheckable->setChecked(false);

    aboutAction = refMenu->addAction("", this, SLOT(About()));
    refMenu->addSeparator();
    helpAction = refMenu->addAction("", this, SLOT(Help()), Qt::Key_F1);

    aboutForm = new AboutForm(this);
    helpForm = new HelpForm(this);

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
    viewMenu->setTitle(tr("&View"));
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

    aboutAction->setText(tr("&About"));
    helpAction->setText(tr("&Help"));

    aboutForm->RetranslateUi(lang);
    helpForm->RetranslateUi(lang);
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
