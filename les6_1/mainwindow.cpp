#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMdiArea>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    setWindowTitle("MDI Example");
    filter = trUtf8("Text File(*.txt)");

    fileMenu = new QMenu(this);
    menuBar()->addMenu(fileMenu);
    fileMenu->setTitle("&File");

    newFile = fileMenu->addAction("&New", this, SLOT(NewFile()), Qt::CTRL + Qt::Key_N);
    openFile = fileMenu->addAction("&Open", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    saveFile = fileMenu->addAction("&Save", this, SLOT(SaveFile()), Qt::CTRL + Qt::Key_S);
    fileMenu->addSeparator();
    exit = fileMenu->addAction("&Exit", this, SLOT(Exit()), Qt::ALT + Qt::Key_F4);

    area = new QMdiArea(this);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setCentralWidget(area);
}

void MainWindow::NewFile()
{
    QTextEdit* textEdit = new QTextEdit(this);
    area->addSubWindow(textEdit);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->setWindowTitle("New Document");
    textEdit->show();
}

void MainWindow::OpenFile()
{
    QMdiSubWindow* subWindow = area->activeSubWindow();
    QTextEdit* textEdit;
    if(!subWindow)
    {
        textEdit = new QTextEdit(this);
        area->addSubWindow(textEdit);
        textEdit->setAttribute(Qt::WA_DeleteOnClose);
        textEdit->show();
    }
    else
    {
        textEdit = qobject_cast<QTextEdit*>(subWindow->widget());
    }

    if (textEdit)
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
                    textEdit->setText(stream.readAll());
                    QFileInfo fileInfo(file.fileName());
                    textEdit->setWindowTitle(fileInfo.fileName());
                    file.close();
                }
            }
        }
    }

;}

void MainWindow::SaveFile()
{
    QMdiSubWindow* subWindow = area->activeSubWindow();
    QTextEdit* textEdit = qobject_cast<QTextEdit*>(subWindow->widget());

    QString path = QFileDialog::getSaveFileName(this, "Save File As", QDir::current().path(), filter);
    if (path.length() > 0)
    {
        QString ext = QString(&(path.data()[path.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(path);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << textEdit->toPlainText();
                file.close();
                QFileInfo fileInfo(file.fileName());
                textEdit->setWindowTitle(fileInfo.fileName());
            }
        }
    }
}

void MainWindow::Exit()
{
    this->close();
}
