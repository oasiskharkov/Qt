#include "filefinderform.h"
#include "ui_filefinderform.h"

#include <QFileDialog>
#include <QMessageBox>

FileFinderForm::FileFinderForm(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::FileFinderForm},
    searchStopped{true}
{
    ui->setupUi(this);
    Init();
}

FileFinderForm::~FileFinderForm()
{
    ResetFinder();
    delete ui;
}

void FileFinderForm::RetranslateUi()
{
    setWindowTitle(tr("Find File"));

    ui->fileName_label->setText(tr("File Name"));
    ui->findIn_label->setText(tr("Find In"));
    ui->clear_pushButton->setText(tr("Clear"));
    ui->path_pushButton->setText(tr("Path"));
    ui->search_pushButton->setText(tr("Search"));
    ui->stop_pushButton->setText(tr("Stop"));
    ui->open_pushButton->setText(tr("Open"));
}

void FileFinderForm::ResetView()
{
    SetupButtons();
    Clear();
}

void FileFinderForm::Clear()
{
    ui->fileName_lineEdit->clear();
    ui->path_lineEdit->clear();
    model.removeRows(0, model.rowCount());
    SetupButtons();
}

void FileFinderForm::InputPath()
{
    QString path = QFileDialog::getExistingDirectory(0, tr("Select Folder"), "");
    if(!path.isEmpty())
    {
        ui->path_lineEdit->setText(path);
    }
}

void FileFinderForm::SearchFile()
{
    if(ui->fileName_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Input file name, please!");
        return;
    }

    if(ui->path_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Input path, please!");
        return;
    }

    ResetFinder();
    finder = QSharedPointer<Finder>::create(ui->path_lineEdit->text().trimmed(), ui->fileName_lineEdit->text().trimmed());
    if(finder)
    {
        finder->start(QThread::NormalPriority);
        searchStopped = false;
        model.removeRows(0, model.rowCount());
        SetupButtons();
        connect(finder.get(), &Finder::ThreadStopped, this, &FileFinderForm::SearchStopped);
        connect(finder.get(), &Finder::FileFound, this, &FileFinderForm::WriteEntryToList);
    }
}

void FileFinderForm::StopSearch()
{
    ResetFinder();
    SetupButtons();
}

void FileFinderForm::OpenSelectedFile()
{
    QMutexLocker locker{&mutex};
    if(!selectionModel.selectedIndexes().isEmpty())
    {
        int row = selectionModel.selectedIndexes().first().row();
        QString path = model.data(model.index(row, 0)).toString();
        ResetFinder();
        emit OpenFoundFile(path);
        close();
    }
}

void FileFinderForm::WriteEntryToList(const QString& path)
{
    QMutexLocker locker{&mutex};
    if(model.insertRow(model.rowCount()))
    {
        QModelIndex index = model.index(model.rowCount() - 1, 0);
        model.setData(index, path);
        SetupButtons();
    }
}

void FileFinderForm::SearchStopped()
{
    StopSearch();
}

void FileFinderForm::Init()
{
    setWindowFlags(Qt::Dialog);

    connect(ui->clear_pushButton, &QPushButton::clicked, this, &FileFinderForm::Clear);
    connect(ui->path_pushButton, &QPushButton::clicked, this, &FileFinderForm::InputPath);
    connect(ui->search_pushButton, &QPushButton::clicked, this, &FileFinderForm::SearchFile);
    connect(ui->stop_pushButton, &QPushButton::clicked, this, &FileFinderForm::StopSearch);
    connect(ui->open_pushButton, &QPushButton::clicked, this, &FileFinderForm::OpenSelectedFile);
    connect(ui->files_listView, &QListView::doubleClicked, this, &FileFinderForm::OpenSelectedFile);

    ui->files_listView->setModel(&model);
    selectionModel.setModel(&model);
    ui->files_listView->setSelectionModel(&selectionModel);

    SetupButtons();
}

void FileFinderForm::ResetFinder()
{
    if(finder)
    {
        if(finder->isRunning())
        {
            finder->Stop(true);
            finder->wait(50);
        }
        finder->quit();
        searchStopped = true;
        finder.reset();
    }
}

void FileFinderForm::SetupButtons()
{
    if(!searchStopped)
    {
        ui->clear_pushButton->setDisabled(true);
        ui->path_pushButton->setDisabled(true);
        ui->search_pushButton->setDisabled(true);
        ui->stop_pushButton->setDisabled(false);
        ui->fileName_lineEdit->setDisabled(true);
        ui->path_lineEdit->setDisabled(true);
    }
    else
    {
        ui->clear_pushButton->setDisabled(false);
        ui->path_pushButton->setDisabled(false);
        ui->search_pushButton->setDisabled(false);
        ui->stop_pushButton->setDisabled(true);
        ui->fileName_lineEdit->setDisabled(false);
        ui->path_lineEdit->setDisabled(false);
    }

    if (model.rowCount())
    {
        ui->open_pushButton->setDisabled(false);
    }
    else
    {
        ui->open_pushButton->setDisabled(true);
    }
}
