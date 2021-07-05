#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include "registerscene.h"
#include "opencvscene.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

#include <mypushbutton.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *);  //重写paintEvent事件
    registerScene *reregisterwidget = NULL;

private:
    Ui::Widget *ui;
    opencvScene faceLand;
    QTcpServer *tcpServer;
    QList<QTcpSocket*>tcpClient;
    QTcpSocket *currentClient;
    MyPushButton *TcpConnectBtn;
    QString fileName;
    QString theFileName;
    QFile *localFile;

    qint64 totalBytes = 0;//总共数据大小
    qint64 bytesWritten = 0;//已发送数据大小
    qint64 bytesToWrite = 0;//还剩数据大小
    qint64 loadSize = 1024;//缓冲区大小
    QByteArray outBlock;//缓存一次发送的数据

    void on_pushButton_Listen_clicked();

private slots:
    void server_New_Connect();
    void socket_Disconnected();
    void on_pushButton_Send_clicked(QString ID);
    void sendFile(QString filePath);
    void socket_Read_Data(void);
};
#endif // WIDGET_H
