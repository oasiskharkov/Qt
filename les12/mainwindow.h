#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inviteform.h"
#include <QTimer>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void SendMessage();
    bool ProcessServiceMessage(const QString& message);
    QString GetNicknameFromServiceMessage(const QString& message) const;

private slots:
    void on_clear_pushButton_clicked();
    void on_timer();
    void on_online_timer();
    void on_nickname_set(const QString& nickname);
    void on_message_lineEdit_returnPressed();
    void on_send_pushButton_clicked();
    void process_pending_datagrams();
    void on_get_users_list(QStringList& usersList);

private:
    Ui::MainWindow *ui;
    InviteForm* invite = nullptr;
    QTimer* timer = nullptr;
    QTimer* online_timer = nullptr;
    QUdpSocket* udpSocket = nullptr;
    QStringListModel* model= nullptr;
    QString nickname;

};
#endif // MAINWINDOW_H
