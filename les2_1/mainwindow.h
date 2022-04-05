#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    std::optional<std::tuple<QString, int, int>> getReplacement(const QString& line) const;

private slots:
    void on_clear_pushButton_pressed();
    void on_value_lineEdit_textEdited(const QString& line);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
