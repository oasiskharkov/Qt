#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>

namespace
{
    QString langs [2] = {"./QtLanguage_en", "./QtLanguage_ru"};
}

MainWindow::MainWindow(QTranslator &translator, QWidget *parent)
    :
      QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , filePath("")
    , translator(translator)
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
    translator.load(langs[0]);

    this->setWindowTitle("Text Editor 2.0");
    filter = trUtf8("Text File(*.txt);;All Files(*.*)");

    QMenu* fileMenu = new QMenu(tr("&File"));
    QMenu* editMenu = new QMenu(tr("&Edit"));
    QMenu* viewMenu = new QMenu(tr("&View"));
    QMenu* refMenu = new QMenu(tr("&Reference"));

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->menuBar()->addMenu(viewMenu);
    this->menuBar()->addMenu(refMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(NewFile()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction(tr("&Open"), this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    fileMenu->addAction(tr("&Read Only"), this, SLOT(ReadOnlyFile()), Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    fileMenu->addAction(tr("&Save"), this, SLOT(SaveFile()), Qt::CTRL + Qt::Key_S);
    fileMenu->addAction(tr("&Save As"), this, SLOT(SaveFileAs()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    fileMenu->addAction(tr("&Close"), this, SLOT(CloseFile()), Qt::CTRL + Qt::SHIFT + Qt::Key_C);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Exit"), this, SLOT(Exit()), Qt::ALT + Qt::Key_F4);

    editMenu->addAction(tr("&Cut"), this, SLOT(Cut()), Qt::CTRL + Qt::Key_X);
    editMenu->addAction(tr("&Copy"), this, SLOT(Copy()), Qt::CTRL + Qt::Key_C);
    editMenu->addAction(tr("&Paste"), this, SLOT(Paste()), Qt::CTRL + Qt::Key_V);
    editMenu->addAction(tr("&Delete"), this, SLOT(Delete()), Qt::CTRL + Qt::Key_D);
    editMenu->addSeparator();
    editMenu->addAction(tr("&Clear"), this, SLOT(Clear()), Qt::CTRL + Qt::Key_K);

    QMenu* langSubMenu = new QMenu(tr("Language"), viewMenu);
    viewMenu->addMenu(langSubMenu);

    engCheckable = langSubMenu->addAction(tr("&English"), this, SLOT(CheckEnglish()));
    engCheckable->setCheckable(true);
    engCheckable->setChecked(true);

    rusCheckable = langSubMenu->addAction(tr("&Russian"), this, SLOT(CheckRussian()));
    rusCheckable->setCheckable(true);
    rusCheckable->setChecked(false);

    refMenu->addAction(tr("&About"), this, SLOT(About()));
    refMenu->addSeparator();
    refMenu->addAction(tr("&Help"), this, SLOT(Help()), Qt::Key_F1);

    aboutForm = new AboutForm(this);
    helpForm = new HelpForm(this);
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
        translator.load(langs[0]);
        this->update();
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
        translator.load(langs[1]);
        this->update();
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
