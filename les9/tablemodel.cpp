#include "tablemodel.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QColor>

namespace  {
    constexpr int COLUMNS_COUNT = 3;
}

TableModel::TableModel(QObject* parent) :
    QAbstractTableModel{parent}
{
    Init();
}

void TableModel::Init()
{
    entries.append({"Task", "Date", "Priority"});
    LoadData();
}

void TableModel::LoadData()
{
    QFile file("base.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QStringList entry = ParseEntry(in.readLine());
            if(COLUMNS_COUNT == entry.size())
            {
                entries.append(entry);
            }
        }
        file.close();
    }
}

void TableModel::SaveData()
{
    QFile file("base.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        for(int i = 1; i < entries.size(); ++i)
        {
            out << entries.at(i).at(0) << " " << entries.at(i).at(1) << " " << entries.at(i).at(2) << endl;
        }
        file.close();
    }
}

QStringList TableModel::ParseEntry(const QString& line) const
{
    QStringList entry;
    int pos1 = line.indexOf(QRegExp("[0-9]"));
    int pos2 = line.lastIndexOf(' ');
    if(pos1 > 0 && pos2 > pos1)
    {
        QString task = line.left(pos1 - 1).trimmed();
        QString date = line.mid(pos1, pos2 - pos1);
        QString priority = line.right(line.size() - 1 - pos2 );
        entry.append(task);
        entry.append(date);
        entry.append(priority);
    }
    return entry;
}

int TableModel::rowCount(const QModelIndex &) const
{
    return entries.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return entries.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TableDataRole:
    {
        return entries.at(index.row()).at(index.column());
    }
    case HeadingRole:
    {
        if(index.row() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "header";
    return roles;
}

void TableModel::onClose()
{
    SaveData();
}

void TableModel::onRemove(int index)
{
    if(index >= 0 && index < entries.size())
    {
        beginRemoveRows(QModelIndex(), rowCount(), rowCount());
        entries.removeAt(index);
        endRemoveRows();
    }
}

void TableModel::onClear()
{
    beginRemoveRows(QModelIndex(), rowCount(), rowCount());
    entries.erase(entries.begin() + 1, entries.end());
    endRemoveRows();
}

void TableModel::onAdd()
{
    if(aw)
    {
        aw->show();
    }
}

