#include "inviteform.h"
#include "ui_inviteform.h"
#include <QMessageBox>
#include <QRegExp>
#include <QCloseEvent>

InviteForm::InviteForm(QWidget *parent):
    QWidget{parent},
    ui{new Ui::InviteForm}
{
    ui->setupUi(this);
}

InviteForm::~InviteForm()
{
    delete ui;
}

void InviteForm::closeEvent(QCloseEvent* event)
{
    QString nickname = ui->nickname_lineEdit->text().trimmed();
    if(nickname.isEmpty())
    {
        QMessageBox::warning(this, "Empty nickname", "Input nickname, please!");
        event->ignore();
        return;
    }
    if(!CheckNickName(nickname))
    {
        QMessageBox::warning(this, "Incorrect nickname", "Input correct nickname (only letters and digits), please!");
        event->ignore();
        return;
    }
    emit get_users_list(usersList);
    auto it = std::find_if(usersList.begin(), usersList.end(), [nickname](const auto& nick) {return nick == nickname; });
    if(it != usersList.end())
    {
        QMessageBox::warning(this, "Same user", "Choose another nickname, such user is already in list!");
        event->ignore();
        return;
    }

    emit set_nickname(nickname);
    event->accept();
}

void InviteForm::on_ok_pushButton_clicked()
{
    this->close();
}


void InviteForm::on_nickname_lineEdit_returnPressed()
{
    this->close();
}

bool InviteForm::CheckNickName(const QString& nickname) const
{
    QRegExp rx("^[a-zA-Z][a-zA-Z0-9_-]{1,20}$");
    return rx.exactMatch(nickname);
}
