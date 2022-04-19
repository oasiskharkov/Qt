#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

namespace
{
    QVector<QString> langs {"c++", "c#", "java", "js", "php", "python"};
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      model(this)
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
    // activate ability to move rows
    ui->lang_listView->setDragDropMode(QAbstractItemView::InternalMove);

    for(const auto& lang : qAsConst(langs))
    {
        model.appendRow(new QStandardItem(QIcon(":/" + lang), lang));
    }
    ui->lang_listView->setModel(&model);
    ui->lang_lineEdit->installEventFilter(this);
}


void MainWindow::on_iconView_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lang_listView->setViewMode(QListView::IconMode);
        ui->lang_listView->setDragDropMode(QAbstractItemView::InternalMove);
    }
    else
    {
        ui->lang_listView->setViewMode(QListView::ListMode);
        ui->lang_listView->setDragDropMode(QAbstractItemView::InternalMove);
    }
}

void MainWindow::on_deleteLang_button_pressed()
{
    auto selectionModel = ui->lang_listView->selectionModel();
    if(selectionModel)
    {
        if(selectionModel->hasSelection())
        {
            auto index = selectionModel->currentIndex();
            if(index.isValid())
            {
                model.removeRow(index.row());
                ui->lang_listView->setDragDropMode(QAbstractItemView::InternalMove);
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Select a language, please!");
        }
    }
}

void MainWindow::on_addLang_button_pressed()
{
    addLanguage();
}

void MainWindow::on_lang_lineEdit_returnPressed()
{
    addLanguage();
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if(object == ui->lang_lineEdit && event->type() == QEvent::FocusIn)
    {
        QPalette palette;
        palette.setColor(QPalette::Text, Qt::black);

        ui->lang_lineEdit->clear();
        ui->lang_lineEdit->setPalette(palette);
        return false;
    }
    return false;
}

void MainWindow::addLanguage()
{
    QString error = "Empty name";
    QString defaultLanguage = "default";

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::red);

    QString lang = ui->lang_lineEdit->text();
    if(lang.isEmpty())
    {
        ui->lang_lineEdit->setText(error);
        ui->lang_lineEdit->setPalette(palette);
        return;
    }

    quint32 size = model.rowCount();
    for(quint32 i = 0; i < size; ++i)
    {
        QModelIndex index = model.index(i, 0);
        if(model.data(index).toString() == lang)
        {
            QMessageBox::warning(this, "Error", "This language is already in list!");
            ui->lang_lineEdit->clear();
            return;
        }
    }

    bool found = (langs.indexOf(lang.toLower()) != -1);
    model.insertRow(0, new QStandardItem(QIcon(":/" + (found ? lang : defaultLanguage)), lang));
    ui->lang_lineEdit->clear();
}
