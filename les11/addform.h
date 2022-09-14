#ifndef ADDFORM_H
#define ADDFORM_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class AddForm;
}

class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = nullptr);
    ~AddForm();
    void reset_values();

private slots:
    void on_clear_pushButton_clicked();
    void on_add_pushButton_clicked();

signals:
    void add_entry(const QStringList& entry);

private:
    bool checkDate(const QString& date) const;

private:
    Ui::AddForm *ui;
};

#endif // ADDFORM_H
