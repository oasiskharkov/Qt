#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(this)
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
    QVector<std::tuple<QString, QString, QString>> comps
    {
        {"Pc", "192.168.1.2", "F0:98:9D:00:00:00"},
        {"Atari", "192.168.1.3", "A1:18:3D:B4:32:01"},
        {"Commodore", "192.168.1.4", "DC:A2:66:07:53:68"},
        {"Macintosh", "192.168.1.5", "0A:00:27:00:00:0D"},
        {"Ibm", "192.168.1.6", "80:CE:62:F2:73:9A"},
        {"Hp", "192.168.1.7", "21:AB:13:D2:00:0A"},
        {"Amiga", "192.168.1.8", "44:F2:27:A4:01:22"},
    };

    model.setColumnCount(3);
    model.setHeaderData(0, Qt::Orientation::Horizontal, QObject::tr("Name"));
    model.setHeaderData(1, Qt::Orientation::Horizontal, QObject::tr("Ip"));
    model.setHeaderData(2, Qt::Orientation::Horizontal, QObject::tr("Mac"));

    for(const auto& comp : comps)
    {
        const auto& [name, ip, mac] = comp;
        model.appendRow({new QStandardItem(name), new QStandardItem(ip), new QStandardItem(mac)});
    }

    ui->comp_tableView->setModel(&model);
    ui->comp_tableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    ui->comp_tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->comp_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comp_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_paint_pushButton_pressed()
{
    auto selectionModel = ui->comp_tableView->selectionModel();
    if(selectionModel)
    {
        if(selectionModel->hasSelection())
        {
            auto indecies = selectionModel->selectedIndexes();
            for (const auto& index : indecies)
            {
                auto item = model.itemFromIndex(index);
                QBrush brush(Qt::GlobalColor::red);
                item->setBackground(brush);
                ui->comp_tableView->clearSelection();
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Select rows, please!");
        }
    }
}

void MainWindow::on_clear_pushButton_pressed()
{
    for (qint32 i = 0; i < model.rowCount(); ++i)
    {
        for (qint32 j = 0; j < model.columnCount(); ++j)
        {
            auto item = model.item(i, j);
            QBrush brush(Qt::GlobalColor::white);
            item->setBackground(brush);
            ui->comp_tableView->clearSelection();
        }
    }
}

