#include "mainview.h"
#include "ui_mainview.h"
#include <QMessageBox>

static int SERVERPORT = 22;

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView), m_Server(new QTcpServer(this)), m_Socket(nullptr)
{
    ui->setupUi(this);
    ui->btnStopServer->setEnabled(false);
    connect(m_Server, &QTcpServer::newConnection, this, &MainView::ExchangeData);
}

MainView::~MainView()
{
    delete ui;
}


void MainView::on_btnStartSever_clicked()
{
   if (StartServer()){
        ui->btnStartSever->setEnabled(false);
        ui->btnStopServer->setEnabled(true);
   }
}

void MainView::on_btnStopServer_clicked()
{
    StopServer();
    ui->btnStartSever->setEnabled(true);
    ui->btnStopServer->setEnabled(false);
}

bool MainView::StartServer(){

    bool result = m_Server->listen(QHostAddress::Any, SERVERPORT);
    if (!result){
        QMessageBox::warning(this,"Echo Server",
                             tr("Unable to start the server: %1")
                             .arg(m_Server->errorString()));

        return false;
    }

    return true;
}

void MainView::StopServer(){

    m_Server->close();
    if (m_Socket!=nullptr && m_Socket->isOpen()){

        m_Socket->close();
    }

}

void MainView::ExchangeData() {

    m_Socket = m_Server->nextPendingConnection();
    if (m_Socket->isOpen()){

        connect(m_Socket, &QTcpSocket::readyRead, this, &MainView::EchoReadData);

    }

}

void MainView::EchoReadData(){

    m_Socket->write("<echoserver>\n");
    QString result;
    while (!m_Socket->atEnd()){
        result.append(m_Socket->readAll());
        m_Socket->waitForReadyRead(200);
    }

    m_Socket->write(qPrintable(result));
    m_Socket->write("</echoserver>\n");

}

