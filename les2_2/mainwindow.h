#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QCustomItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    QCustomItemModel(QObject* parent = Q_NULLPTR) : QStandardItemModel(parent)
    {
    }

    Qt::ItemFlags flags (const QModelIndex & index) const override
    {
        Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
        if (index.isValid()){
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
        }
        return defaultFlags;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void Init();
    bool eventFilter(QObject* object, QEvent* event) override;
    void addLanguage();

private slots:
    void on_iconView_checkBox_stateChanged(int arg1);
    void on_deleteLang_button_pressed();
    void on_addLang_button_pressed();
    void on_lang_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QCustomItemModel model;
};
#endif // MAINWINDOW_H
