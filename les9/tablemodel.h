#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "addwidget.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    enum TableRoles {
        TableDataRole = Qt::UserRole + 1,
        HeadingRole

    };

private:
    void Init();
public:   
    TableModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void onClear();
    Q_INVOKABLE void onClose();
    Q_INVOKABLE void onRemove(int index);
    Q_INVOKABLE void onAdd();

private:
    void LoadData();
    void SaveData();
    QStringList ParseEntry(const QString& line) const;
    QVector<QStringList> entries;
    AddWidget* aw;
};

#endif // TABLEMODEL_H
