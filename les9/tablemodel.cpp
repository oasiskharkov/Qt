#include "tablemodel.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QColor>
#include <QtDebug>

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
    entries.append({"", "Task", "Date", "Priority"});
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
            QStringList entry = parseEntry(in.readLine());
            if(COLUMNS_COUNT == entry.size())
            {
                entry.insert(0, "");
                entries.append(entry);
            }
            else
            {
                qWarning() << "Incorrect entry";
            }
        }
        file.close();
        qInfo() << "Data loaded successfully!";
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
            out << entries.at(i).at(1) << " " << entries.at(i).at(2) << " " << entries.at(i).at(3) << endl;
        }
        file.close();
        qInfo() << "Data saved successfully!";
    }
}

QStringList TableModel::parseEntry(const QString& line) const
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
    else
    {
        qDebug() << "Incorrect entry parsing!";
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
        if(index.column() == 0)
        {
            if(index.row() == 0)
            {
                return "#";
            }
            return QString::number(index.row());
        }
        else
        {
            return entries.at(index.row()).at(index.column());
        }
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

void TableModel::onSave()
{
    SaveData();
}

void TableModel::onRemove(int index)
{
    if(index >= 0 && index < entries.size())
    {
        beginRemoveRows(QModelIndex(), 0, rowCount());
        entries.removeAt(index);
        endRemoveRows();
    }
    else
    {
        qWarning() << "Incorrect index. Can't remove entry!";
    }
}

void TableModel::onClear()
{
    if(entries.size() >= 1)
    {
        beginRemoveRows(QModelIndex(), 0, rowCount());
        entries.erase(entries.begin() + 1, entries.end());
        endRemoveRows();
    }
    else
    {
        qWarning() << "Incorrect data table. Can't clear entries!";
    }
}

void TableModel::onAdd(const QString& task, const QString& date, const QString& priority)
{                     
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    entries.append(QStringList{"", task, date, priority});
    endInsertRows();
}

int TableModel::entriesCount() const
{
    int count = entries.size() - 1;
    if (count < 0)
    {
        qWarning() << "Incorrect data table! Can't count entries!";
    }
    return count;
}

bool TableModel::checkDate(const QString& date)
{
    QRegExp rx("(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[012])[-/.](19\\d{2}|20\\d{2})");
    return rx.exactMatch(date);
}

QStringList TableModel::getRow(int index) const
{
    if(index >= 0 && index < entries.size())
    {
        return entries.at(index);
    }
    return QStringList{};
}

bool TableModel::findTask(const QString& task) const
{
    auto it = std::find_if(entries.begin(), entries.end(), [task](const auto& entry) { return entry[1] == task; });
    if(it != entries.end())
    {
        return true;
    }
    return false;
}

