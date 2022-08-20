#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , invite{new InviteForm(parent)}
    , timer{new QTimer(parent)}
    , online_timer{new QTimer(parent)}
    , udpSocket{new QUdpSocket(parent)}
    , model{new QStringListModel(parent)}
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer);
    connect(online_timer, &QTimer::timeout, this, &MainWindow::on_online_timer);
    connect(invite, &InviteForm::set_nickname, this, &MainWindow::on_nickname_set);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::process_pending_datagrams);
    connect(invite, &InviteForm::get_users_list, this, &MainWindow::on_get_users_list);

    timer->setSingleShot(true);
    timer->setInterval(500);
    timer->start();

    online_timer->setInterval(1000);

    ui->message_lineEdit->setFocus();
    ui->users_listView->setModel(model);

    udpSocket->bind(45454, QUdpSocket::ShareAddress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QByteArray datagram = ("#quit:" + nickname).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    event->accept();
}

void MainWindow::SendMessage()
{
    QString message = ui->message_lineEdit->text().trimmed();
    if(message.isEmpty())
    {
        QMessageBox::warning(this, "Empty message", "Input message, please!");
        return;
    }
    ui->message_lineEdit->clear();
    QByteArray datagram = (nickname + ": " + message).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

bool MainWindow::ProcessServiceMessage(const QString& message)
{
    if(message.indexOf("#quit:") == 0)
    {
        const QString& nickname = GetNicknameFromServiceMessage(message);
        if(!nickname.isEmpty())
        {
            auto list = model->stringList();
            auto it = std::find_if(list.begin(), list.end(), [nickname](const auto& nick) { return nick == nickname; });
            if (it != list.end())
            {
                model->removeRow(it - list.begin());
            }
        }
        return true;
    }
    else if(message.indexOf("#online:") == 0)
    {
        const QString& nickname = GetNicknameFromServiceMessage(message);
        if(!nickname.isEmpty())
        {
            auto list = model->stringList();
            auto it = std::find_if(list.begin(), list.end(), [nickname](const auto& nick) { return nick == nickname; });
            if (it == list.end())
            {
                if(model->insertRow(model->rowCount()))
                {
                    QModelIndex index = model->index(model->rowCount() - 1, 0);
                    model->setData(index, nickname);
                }
            }
        }
        return true;
    }
    return false;
}

QString MainWindow::GetNicknameFromServiceMessage(const QString& message) const
{
    int index = message.lastIndexOf(':');
    if (index != -1 && index + 1 < message.length())
    {
        QString nickname = message.right(message.length() - index - 1);
        return nickname;
    }
    return "";
}

void MainWindow::on_clear_pushButton_clicked()
{
    ui->chat_textEdit->clear();
    ui->message_lineEdit->setFocus();
}

void MainWindow::on_timer()
{
    invite->show();
}

void MainWindow::on_online_timer()
{
    QByteArray datagram = ("#online:" + nickname).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

void MainWindow::on_nickname_set(const QString& nickname)
{
    this->nickname = nickname;
    if(model->insertRow(model->rowCount()))
    {
        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, nickname);
    }
    this->setWindowTitle("Chat (user: " + nickname + ")");
    online_timer->start();
}

void MainWindow::on_message_lineEdit_returnPressed()
{
    SendMessage();
}

void MainWindow::on_send_pushButton_clicked()
{
    SendMessage();
}

void MainWindow::process_pending_datagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams())
    {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString message = datagram.constData();
        if(!ProcessServiceMessage(message))
        {
            ui->chat_textEdit->append(message);
        }
    }
}

void MainWindow::on_get_users_list(QStringList& usersList)
{
    usersList = model->stringList();
}

