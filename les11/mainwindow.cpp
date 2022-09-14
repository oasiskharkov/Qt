#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , addForm{new AddForm{parent}}
    , model{this, QSqlDatabase::addDatabase("QSQLITE")}
    , id{0}
{
    ui->setupUi(this);

    QObject::connect(addForm, &AddForm::add_entry, this, &MainWindow::on_add_enrty);

    addEntry = "INSERT INTO Organizer (id, task, date, priority) VALUES ('%1', '%2', '%3', '%4')";
    removeAll = "DELETE FROM Organizer";
    dropTable = "DROP TABLE Organizer";
    maxId = "SELECT MAX(id) FROM Organizer";

    auto db = model.database();
    db.setDatabaseName("./database.db");
    if (!db.open())
    {
        qDebug() << "Can't open database";
        return;
    }
    QSqlQuery query{db};

    bool res = query.exec("CREATE TABLE IF NOT EXISTS Organizer (id INTEGER PRIMARY KEY NOT NULL, task VARCHAR(256), date DATE NOT NULL, priority INTEGER NOT NULL)");
    if (!res)
    {
        qDebug() << "Can't create table 'Organizer'";
        qDebug() << model.lastError().text();
        return;
    }

    res = query.exec(maxId);
    if (!res)
    {
        qDebug() << "Can't find max index";
        qDebug() << model.lastError().text();
        return;
    }

    if (query.next()) {
        id = query.value(0).toInt() + 1;
    }

    model.setTable("Organizer");
    model.select();
    ui->db_tableView->setModel(&model);
    ui->db_tableView->setColumnHidden(0, true);
    ui->db_tableView->setColumnWidth(1, 483);
    ui->db_tableView->setColumnWidth(2, 70);
    ui->db_tableView->setColumnWidth(3, 70);
    ui->db_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_pushButton_clicked()
{
    if(addForm)
    {
        addForm->show();
        addForm->reset_values();
    }
}

void MainWindow::on_remove_pushButton_clicked()
{
    if(model.rowCount() == 0)
    {
         QMessageBox::warning(this, "Table is empty", "There are no entries!");
         return;
    }

    auto selectionModel = ui->db_tableView->selectionModel();
    if(selectionModel)
    {
        if(selectionModel->hasSelection())
        {
            auto indexes = selectionModel->selection().indexes();
            for(const auto& index: qAsConst(indexes))
            {
                if(index.isValid())
                {
                    model.removeRow(index.row());
                }
            }
            model.select();
        }
        else
        {
            QMessageBox::warning(this, "Error", "Select entry, please!");
        }
    }
}

void MainWindow::on_clear_pushButton_clicked()
{
    if(model.rowCount() == 0)
    {
         QMessageBox::warning(this, "Table is empty", "There are no entries!");
         return;
    }

    QSqlQuery query{db};
    bool res = query.exec(removeAll);
    if (!res)
    {
        qDebug() << "Can't remove all entries";
        qDebug() << model.lastError().text();
        return;
    }
    model.select();
}

void MainWindow::on_close_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_add_enrty(const QStringList& entry)
{
    if (entry.size() != 3)
    {
        QMessageBox::warning(this, "Entry error", "Incorrect entry!");
        return;
    }

    QSqlQuery query{db};
    bool res = query.exec(addEntry.arg(QString::number(id++)).arg(entry.at(0)).arg(entry.at(1)).arg(entry.at(2)));
    if (!res)
    {
        qDebug() << "Can't insert entry";
        qDebug() << model.lastError().text();
        return;
    }
    model.select();
}

