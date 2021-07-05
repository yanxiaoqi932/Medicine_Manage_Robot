#include "storehousescene.h"
#include "mypushbutton.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include <windows.h>

QString portName2;
QString readData;
static int num_read;
bool IS_read = 0;  //是否已经读取串口信息
QString qualityData;  //存储所读取的质量信息
storehouseScene::storehouseScene()
{
    widget = NULL;
    this->setFixedSize(1600,900);
    serial2 = new QSerialPort(this);

    //扫描串口
    serialportMedicineOpen();

    //打开串口
    MyPushButton *openSerialBtn = new MyPushButton;
    openSerialBtn->setParent(this);
    openSerialBtn->resize(120,75);
    openSerialBtn->move(this->width()*0.7,this->height()*0.7);
    openSerialBtn->setText("查看");
    openSerialBtn->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    connect(openSerialBtn,&MyPushButton::clicked,[=](){
        openSerialBtn->zoom1();
        openSerialBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            serialportRead(serial2);
        });
    });
    //返回按钮
    MyPushButton *storeBckBtn = new MyPushButton;
    storeBckBtn->setParent(this);
    storeBckBtn->resize(120,75);
    storeBckBtn->move(this->width()*0.7,this->height()*0.8);
    storeBckBtn->setText("返回");
    storeBckBtn->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    connect(storeBckBtn,&MyPushButton::clicked,[=](){
        storeBckBtn->zoom1();
        storeBckBtn->zoom2();
        QTimer::singleShot(200,this,[=](){
            emit this->storeBck();
        });

    });



    //读取信息
    connect(serial2, SIGNAL(readyRead()), this, SLOT(on_SerialPort_readyRead2()));




}

//扫描串口
void storehouseScene::serialportMedicineOpen()
{
    foreach(const QSerialPortInfo &Info,QSerialPortInfo ::availablePorts())
        {
            QSerialPort CurrentPort;
            CurrentPort.setPort(Info);
            if(CurrentPort.open(QIODevice::ReadWrite))
            {
                qDebug()<<"port:" + CurrentPort.portName() + "扫描成功";
                portName2 = CurrentPort.portName();
                CurrentPort.close();   //先开再关，把串口名称先导入
            }

        }

}

//打开串口发送读取消息
void storehouseScene::serialportRead(QSerialPort *serial2)
{
    serial2->setPortName(portName2);  //设置串口名称
    if(serial2->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口";
    }

    serial2->setBaudRate(QSerialPort::Baud9600);  //设置波特率
    serial2->setDataBits(QSerialPort::Data8);  //设置数据位
    serial2->setParity(QSerialPort::NoParity);  //设置是否奇偶校验
    serial2->setStopBits(QSerialPort::OneStop);  //设置停止位
    serial2->setFlowControl(QSerialPort::NoFlowControl);  //设置是否流控制
    serial2->setDataTerminalReady(false);
    serial2->setRequestToSend(false);

    QString storeSignal = "@\n";
    QByteArray storeArraySignal = storeSignal.toLatin1();
    qDebug()<<"写入:"+storeArraySignal;
    serial2->write(storeArraySignal);
    qDebug()<<"写入语句";
}

//接收串口数据
void storehouseScene::on_SerialPort_readyRead2()
{
    QByteArray recvData;

    if(serial2->isOpen())
    {
        qDebug()<<"开始读取数据";
        recvData = serial2->readAll();
        readData.prepend(recvData);
        qualityData = QString(readData);
        qDebug() <<"接收：" + QString(readData);
        IS_read = 1;
        num_read++;
    }

    if(widget!=NULL){
         widget->hide();
         widget=NULL;
       }
       widget=new QWidget(this);
       widget->setGeometry(0,120,1600,600);

       QPushButton *btn1=new QPushButton("附子",widget);
       btn1->setGeometry(20,0,120,75);
       if(qualityData.at(0) == '0')
       {
           btn1->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn1->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn2=new QPushButton("干姜",widget);
       btn2->setGeometry(180,0,120,75);
       if(qualityData.at(1) == '0')
       {
           btn2->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn2->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn3=new QPushButton("肉桂",widget);
       btn3->setGeometry(340,0,120,75);
       if(qualityData.at(2) == '0')
       {
           btn3->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn3->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn4=new QPushButton("丁香",widget);
       btn4->setGeometry(500,0,120,75);
       if(qualityData.at(3) == '0')
       {
           btn4->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn4->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn5=new QPushButton("茴香",widget);
       btn5->setGeometry(640,0,120,75);
       if(qualityData.at(4) == '0')
       {
           btn5->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn5->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn6=new QPushButton("茱萸",widget);
       btn6->setGeometry(800,0,120,75);
       if(qualityData.at(5) == '0')
       {
           btn6->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn6->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn7=new QPushButton("杜仲",widget);
       btn7->setGeometry(960,0,120,75);
       if(qualityData.at(6) == '0')
       {
           btn7->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn7->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn8=new QPushButton("鱼腥草",widget);
       btn8->setGeometry(1120,0,120,75);
       if(qualityData.at(7) == '0')
       {
           btn8->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn8->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn9=new QPushButton("金银花",widget);
       btn9->setGeometry(1280,0,120,75);
       if(qualityData.at(8) == '0')
       {
           btn9->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn9->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn10=new QPushButton("菊花",widget);
       btn10->setGeometry(20,200,120,75);
       if(qualityData.at(9) == '0')
       {
           btn10->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn10->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn11=new QPushButton("菊花",widget);
       btn11->setGeometry(180,200,120,75);
       if(qualityData.at(10) == '0')
       {
           btn11->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn11->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn12=new QPushButton("夏枯草",widget);
       btn12->setGeometry(340,200,120,75);
       if(qualityData.at(11) == '0')
       {
           btn12->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn12->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn13=new QPushButton("连翘",widget);
       btn13->setGeometry(500,200,120,75);
       if(qualityData.at(12) == '0')
       {
           btn13->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn13->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn14=new QPushButton("薄荷",widget);
       btn14->setGeometry(640,200,120,75);
       if(qualityData.at(13) == '0')
       {
           btn14->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn14->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn15=new QPushButton("冰片",widget);
       btn15->setGeometry(800,200,120,75);
       if(qualityData.at(14) == '0')
       {
           btn15->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn15->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn16=new QPushButton("茨实",widget);
       btn16->setGeometry(960,200,120,75);
       if(qualityData.at(15) == '0')
       {
           btn16->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn16->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn17=new QPushButton("茯苓",widget);
       btn17->setGeometry(1120,200,120,75);
       if(qualityData.at(16) == '0')
       {
           btn17->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn17->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }

       QPushButton *btn18=new QPushButton("山药",widget);
       btn18->setGeometry(1280,200,120,75);
       if(qualityData.at(17) == '0')
       {
           btn18->setStyleSheet("background:rgb(255,0,0);border-radius:10px;padding:2px 4px;");
       }
       else
       {
           btn18->setStyleSheet("background:rgb(0,255,0);border-radius:10px;padding:2px 4px;");
       }




       widget->show();



}



storehouseScene::~storehouseScene()
{
    serial2->setPortName(portName2);
    serial2->close();
    num_read = 0;
    readData.clear();
    delete serial2;
    delete widget;
}


