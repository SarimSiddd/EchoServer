#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = nullptr);
    ~MainView();

private slots:
    void on_btnStartSever_clicked();

    void on_btnStopServer_clicked();

private:
    Ui::MainView *ui;
    QTcpServer* m_Server;
    QTcpSocket* m_Socket;
    bool StartServer();
    void StopServer();
    void ExchangeData();
    void EchoReadData();
};
#endif // MAINVIEW_H
