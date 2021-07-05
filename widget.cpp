#include "widget.h"
#include "ui_widget.h"
#include "loadbutton.h"
#include "registerbutton.h"
#include "clientscene.h"
#include "doctorscene.h"
#include "registerscene.h"
#include "mypushbutton.h"
#include <QTextCodec>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QPalette>
#include <QMessageBox>
#include <windows.h>

QString ID;
quint16 currentIP;  //存储当前连接的客户端IP地址
bool IsConnected;   //存储当前是否有客户端连接
extern QString IDSend;   //与注册界面共享ID
extern QString ID_opencv;  //人脸识别函数与widget界面共享的数据，用于传递识别出的用户的ID
extern bool IS_Land_OK;  //人脸识别函数与widget界面共享的数据，用于判断是否识别成功
//存储客户端发来的文件消息
QString IDclient;
QString contentClient;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建基础登陆界面
    this->setFixedSize(1600,900);
    this->setWindowTitle("中药通人机交互系统");

    //创建登陆按钮
    MyPushButton *LandBtn = new MyPushButton;
    LandBtn->setParent(this);
    LandBtn->resize(150,65);
    LandBtn->move(this->width()*0.8,this->height()*0.75);
    LandBtn->setText("账号登陆");


    LandBtn->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    //文字
    QFont font;       //设置label字体
    font.setPointSize(23);
    font.setFamily("黑体");


    //用户编号输入框
    ui->lineEditID->move(this->width()*0.64,this->height()*0.4);
    ui->lineEditID->setMinimumWidth(400);
    ui->lineEditID->setMinimumHeight(50);
    ui->lineEditID->setMaxLength(400);
    QLabel *loadLabel = new QLabel;
    loadLabel->setParent(this);
    font.setPointSize(15);
    loadLabel->setFont(font);
    loadLabel->setText(QString("用户编号"));
    loadLabel->setGeometry(QRect(this->width()*0.6-90,this->height()*0.4,120,50));

    //用户密码输入框
    ui->lineEditPassWord->move(this->width()*0.64,this->height()*0.5);
    ui->lineEditPassWord->setMinimumWidth(400);
    ui->lineEditPassWord->setMinimumHeight(50);
    ui->lineEditPassWord->setMaxLength(400);
    QLabel *passwordLabel = new QLabel;
    passwordLabel->setParent(this);
    font.setPointSize(15);
    passwordLabel->setFont(font);
    passwordLabel->setText(QString("用户密码"));
    passwordLabel->setGeometry(QRect(this->width()*0.6-90,this->height()*0.5,120,50));

    //创建注册按钮
    registerButton *registBtn = new registerButton(":/res1/register.png");
    registBtn->setParent(this);
    registBtn->move(this->width()*0.665,this->height()*0.6);

    //创建消息栏
    QLabel *ImformationLabel = new QLabel;
    ImformationLabel->setParent(this);
    font.setPointSize(15);
    ImformationLabel->setFont(font);
    ImformationLabel->setGeometry(QRect(this->width()*0.8,this->height()*0.6,120,50));


    //注册跳跃特效实现
    connect(registBtn,&registerButton::clicked,[=](){
    registBtn->zoom1();
    registBtn->zoom2();

    QTimer::singleShot(500,this,[=](){
        registerScene *registerwidget = new registerScene();
        this->hide();
        registerwidget->setGeometry(this->geometry());
        registerwidget->setFixedSize(1600,900);
        registerwidget->setWindowTitle("新用户注册界面");
        registerwidget->show();

        //监听从registerwidget传来的消息
            //监听传送文件消息
        connect(registerwidget,&registerScene::sendFileToClient,[=](){
            qDebug()<<"开始发送文件";
            on_pushButton_Send_clicked(IDSend);
            Sleep(1000);
            QString dirPath = QString("AllData") + QString("/") + IDSend;
            sendFile(dirPath + QString("/pass.txt"));
            Sleep(200);
            sendFile(dirPath + QString("/name.txt"));
            Sleep(200);
            sendFile(dirPath + QString("/sex.txt"));
            Sleep(200);
            sendFile(dirPath + QString("/age.txt"));
            Sleep(200);
        });

            //监听返回消息
        connect(registerwidget,&registerScene::chooseSceneBack,[=](){
            this->show();
            this->setGeometry(registerwidget->geometry());
            registerwidget->hide();
            delete registerwidget;

        });
    });
     });



    //登陆功能实现
    connect(LandBtn,&MyPushButton::clicked,[=](){
        LandBtn->zoom1();
        LandBtn->zoom2();

        //记录用户ID和密码
        QString ID_Imformation = ui->lineEditID->text();
        QString Pass_Imformation = ui->lineEditPassWord->text();
        QString dirPath;
        dirPath = QString("AllData") + QString("/") + ID_Imformation;

        QDir IDDir(dirPath);        //用户对应文件夹
        QFile Passfile(dirPath + QString("/pass.txt"));  //密码文档

        QString real_password;   //储存得到的真实密码
        //开启账户和密码的比对
        ImformationLabel->clear();
        if(!IDDir.exists())
        {
            ImformationLabel->clear();
            ImformationLabel->setText(QString("账户错误!"));
        }
        else
        {
            if(!Passfile.open(QIODevice::ReadOnly))
            {
                ImformationLabel->clear();
                ImformationLabel->setText(QString("密码错误!"));
                Passfile.close();
            }
            else
            {
                QTextStream in_pass(&Passfile);
                while(!in_pass.atEnd())
                {
                    real_password  = in_pass.readLine();
                }
                Passfile.close();

                //进入患者界面
                if((real_password == Pass_Imformation)&&(real_password != "323746"))
                {
                    qDebug()<<"账户和密码正确!";
                    ID = ID_Imformation;
                    QTimer::singleShot(500,this,[=](){
                         clientScene *clientWidget = new clientScene;    //定义用户的专有界面
                         clientWidget->show();
                         //clientWidget->setGeometry(this->geometry());
                         clientWidget->setWindowTitle("患者界面");
                         this->hide();

                         //监听从clientScene传来的返回信息
                         connect(clientWidget,&clientScene::chooseSceneBack,[=](){
                             this->show();
                             clientWidget->hide();
                             //this->setGeometry(clientWidget->geometry());
                             delete clientWidget;
                             ui->lineEditID->clear();
                             ui->lineEditPassWord->clear();
                         });
                    });
                }

                //进入医生界面
                else if((real_password == Pass_Imformation)&&(real_password == "323746"))
                {
                    QTimer::singleShot(500,this,[=](){
                        doctorScene *doctorWidget = new doctorScene;
                        doctorWidget->show();
                        doctorWidget->setGeometry(this->geometry());
                        doctorWidget->setWindowTitle("医生界面");
                        this->hide();

                        //监听从doctorScene传来的返回消息
                        connect(doctorWidget,&doctorScene::doctorSceneBack,[=](){
                            this->show();
                            doctorWidget->hide();
                            this->setGeometry(doctorWidget->geometry());
                            delete doctorWidget;
                            ui->lineEditID->clear();
                            ui->lineEditPassWord->clear();
                        });
                    });


                }
                else
                {
                    ImformationLabel->clear();
                    ImformationLabel->setText(QString("密码错误!"));
                }
            }
        }
    });

    //创建人脸识别登陆按钮
    MyPushButton *faceLandBtn = new MyPushButton;
    faceLandBtn->setParent(this);
    faceLandBtn->resize(150,65);
    faceLandBtn->move(this->width()*0.6,this->height()*0.75);
    faceLandBtn->setText("扫脸登陆");


    faceLandBtn->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");


    connect(faceLandBtn,&MyPushButton::clicked,[=](){
        faceLandBtn->zoom1();
        faceLandBtn->zoom2();

        QTimer::singleShot(500,this,[=](){
            faceLand.on_action_FaceRecognition_triggered();
            if(IS_Land_OK == true)
            {
                IS_Land_OK = false;
                qDebug()<<"识别成功!";
                ID = ID_opencv;
                QTimer::singleShot(500,this,[=](){
                     clientScene *clientWidget = new clientScene;    //定义用户的专有界面
                     clientWidget->show();
                     clientWidget->setWindowTitle("患者界面");
                     this->hide();

                     //监听从clientScene传来的返回信息
                     connect(clientWidget,&clientScene::chooseSceneBackFace,[=](){
                         this->show();
                         clientWidget->hide();
                         delete clientWidget;
                         ui->lineEditID->clear();
                         ui->lineEditPassWord->clear();
                     });
                });
            }
        });
    });

/**********************TCP编程***************************/
    //创建TCP连接/断开按钮
    TcpConnectBtn = new MyPushButton;
    TcpConnectBtn->setParent(this);
    TcpConnectBtn->resize(60,25);
    TcpConnectBtn->move(this->width()*0.6,this->height()*0.6);
    TcpConnectBtn->setText("侦听");
    TcpConnectBtn->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");
    
    //实例化服务器端
    tcpServer = new QTcpServer(this);

    //获取本地端口
    //QString myIP = QNetworkInterface().allAddresses().at(1).toString();
    //qDebug()<<myIP;

    //当客户端连接时，触发槽函数NewConnectionSlot()
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(server_New_Connect()));

    on_pushButton_Listen_clicked();

}

//与客户端进行连接
void Widget::server_New_Connect()
{
    //获取客户端连接
    currentClient = tcpServer->nextPendingConnection();
    qDebug()<<"获取客户端连接";
    //连接QTcpSocket的信号槽，以读取新数据
    QObject::connect(currentClient, &QTcpSocket::readyRead, this, &Widget::socket_Read_Data);
    QObject::connect(currentClient, &QTcpSocket::disconnected, this, &Widget::socket_Disconnected);

    qDebug() << "A Client connect!";
}

//读取客户端发来的数据
void Widget::socket_Read_Data()
{
    qDebug()<<"读取客户端数据";
    static int indexContent = 1;
    QByteArray buffer;
    //读取缓冲区数据
    buffer = currentClient->readAll();
    QString contentReceive;
    if(!buffer.isEmpty())
    {
        contentReceive = QString::fromUtf8(buffer);
        qDebug()<<"接收数据";
        qDebug()<<contentReceive;
    }
    buffer.clear();
    switch(indexContent)
    {
    case 1:
        IDclient = contentReceive;break;
    case 2:
        contentClient = contentReceive;break;
    default:
        break;
    }
    //收集到信息后创建文件并写入
    if(indexContent >= 2)
    {
        qDebug()<<"写入文件";
        indexContent = 1;
        QString medicinePath = QString("AllData/") + IDclient + QString("/medicine.txt");
        QFile medicineFile(medicinePath);  //创建名称为medicine.txt的文档
        medicineFile.open(QIODevice::WriteOnly); //加入QIODevice::Text才能换行

        QTextStream medicineContentStream(&medicineFile);  //文件输入流
        medicineContentStream.setCodec("UTF-8");
        medicineContentStream<<contentClient;    //写入文件
        medicineFile.close();

        IDclient.clear();
        contentClient.clear();
        indexContent = 0;
    }

    indexContent++;
}


//对指定端口(8765)进行侦听
void Widget::on_pushButton_Listen_clicked()
{
    if(TcpConnectBtn->text() == tr("侦听"))
    {
        //从输入框获取端口号
        int port = 8765;

        //监听指定的端口
        if(!tcpServer->listen(QHostAddress::Any, port))
        {
            //若出错，则输出错误信息
            qDebug()<<tcpServer->errorString();
            return;
        }
        //修改按键文字
        TcpConnectBtn->setText("取消侦听");
        qDebug()<< "Listen succeessfully!";
    }
    
    else
    {
        //如果正在连接
        if(currentClient->state() == QAbstractSocket::ConnectedState)
        {
            //关闭连接
            currentClient->disconnectFromHost();
        }
        //取消侦听
        currentClient->close();
        //修改按键文字
        TcpConnectBtn->setText("侦听");
        
    }
}

//信号断开的槽函数
void Widget::socket_Disconnected()
{
    //发送按键失能
    //TcpConnectBtn->setEnabled(false);
    qDebug() << "Disconnected!";
}

//服务器发送信息
void Widget::on_pushButton_Send_clicked(QString ID)
{
    qDebug() << "Send: " << ID;
    //获取文本框内容并以ASCII码形式发送
    currentClient->write(ID.toLocal8Bit());
    currentClient->flush();
}

//服务器发送用户信息文件
void Widget::sendFile(QString filePath)
{
    QFile Sendfile(filePath);

    if(!Sendfile.open((QFile::ReadOnly)))
    {//以只读方式打开
        qDebug() <<"---FileServer---无法读取文件 ";
        return;
    }

    qDebug() <<"---FileServer---开始传送文件！";

    QString content;
    content = Sendfile.readAll();
    Sendfile.close();

    qDebug()<<content;
    currentClient->write(content.toUtf8());
    currentClient->flush();
    qDebug()<<"发送完毕！";
    //发送完头数据后剩余数据的大小，即文件实际内容的大小
    //发送成功后会发射SIGNAL(bytesWritten(qint64))

}


Widget::~Widget()
{
    delete ui;
    tcpServer->close();
    tcpServer->deleteLater();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res1/land.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

