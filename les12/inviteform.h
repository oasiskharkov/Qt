#ifndef INVITEFORM_H
#define INVITEFORM_H

#include <QWidget>

namespace Ui {
class InviteForm;
}

class InviteForm : public QWidget
{
    Q_OBJECT

public:
    explicit InviteForm(QWidget *parent = nullptr);
    ~InviteForm();

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void set_nickname(const QString& nickname);

private slots:
    void on_ok_pushButton_clicked();
    void on_nickname_lineEdit_returnPressed();

private:
    void SetNickname();
    bool CheckNickName(const QString& nickname) const;

private:
    Ui::InviteForm *ui;

};

#endif // INVITEFORM_H
