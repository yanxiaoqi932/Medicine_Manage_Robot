#include "clientscene.h"
#include "widget.h"
#include "clientbackbutton.h"
#include "mypushbutton.h"
#include "analysis.h"
#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTextEdit>
#include <QTimer>
#include <Qtxml>
#include <QTableWidget>
#include <QFileDialog>
#include <QAxObject>
#include <QHeaderView>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include <QProgressBar>
#include <windows.h>

QString serialportString;
QByteArray name,sex,age;
QByteArray sendBuffer[20]; //串口发送的消息（分批）
QString portName;
int numSend = 0; //记录串口发送药物消息批次
int composit_score[4]={0,0,0,0};
clientScene::clientScene()
{
    extern  QString ID;
    this->setFixedSize(1600,900);

    QFont font2;
    font2.setPointSize(23);
    font2.setFamily("黑体");

    QString clientID = ID;  //获取客户的ID
    qDebug()<<clientID;
    QString dirpath = "AllData/" + clientID;
    QFile nameFile(dirpath + QString("/name.txt"));
    QFile sexFile(dirpath + QString("/sex.txt"));
    QFile ageFile(dirpath + QString("/age.txt"));
    QString dirpathMedicine = dirpath + QString("/medicine.txt");

    


    //读取客户年龄
    if(nameFile.open(QIODevice::ReadOnly))
    {
        name = nameFile.readAll();
        nameFile.close();
    }

    //读取客户性别
    if(sexFile.open(QIODevice::ReadOnly))
    {
        sex = sexFile.readAll();
        sexFile.close();
    }

    //读取客户年龄
    if(ageFile.open(QIODevice::ReadOnly))
    {
        age = ageFile.readAll();
        ageFile.close();
    }

    font2.setPointSize(15);

    //用户姓名栏
    QLabel *nameEdit = new QLabel;
    nameEdit->setParent(this);
    nameEdit->setFixedSize(120,45);
    nameEdit->move(this->width()*0.2,this->height()*0.2);
    nameEdit->setFont(font2);
    nameEdit->setText(name);
    QLabel *namelabel = new QLabel;
    namelabel->setParent(this);
    font2.setPointSize(15);
    namelabel->setFont(font2);
    namelabel->setText(QString("姓名："));
    namelabel->setGeometry(QRect(this->width()*0.2-70,this->height()*0.2-5,120,50));

    //用户性别栏
    QLabel *sexEdit = new QLabel;
    sexEdit->setParent(this);
    sexEdit->setFixedSize(120,45);
    sexEdit->move(this->width()*0.5,this->height()*0.2);
    sexEdit->setFont(font2);
    sexEdit->setText(sex);
    QLabel *sexlabel = new QLabel;
    sexlabel->setParent(this);
    font2.setPointSize(15);
    sexlabel->setFont(font2);
    sexlabel->setText(QString("性别："));
    sexlabel->setGeometry(QRect(this->width()*0.5-70,this->height()*0.2-5,120,50));

    //用户年龄栏
    QLabel *ageEdit = new QLabel;
    ageEdit->setParent(this);
    ageEdit->setFixedSize(120,45);
    ageEdit->move(this->width()*0.8,this->height()*0.2);
    ageEdit->setFont(font2);
    ageEdit->setText(age);
    QLabel *agelabel = new QLabel;
    agelabel->setParent(this);
    font2.setPointSize(15);
    agelabel->setFont(font2);
    agelabel->setText(QString("年龄："));
    agelabel->setGeometry(QRect(this->width()*0.8-70,this->height()*0.2-5,120,50));
    
    //读取用户的药方
    MyPushButton *readMedicine = new MyPushButton;
    readMedicine->setFixedSize(120,55);
    readMedicine->move(this->width()*0.75,this->height()*0.3);
    readMedicine->setParent(this);
    readMedicine->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");
    readMedicine->setText("查看药方");

    font2.setFamily("宋体");
    font2.setPointSize(15);

    QTableWidget *tableWidget = new QTableWidget(0,3);  //注意，此处的行不包括表头！
    tableWidget->resize(450,320);
    tableWidget->setFont(font2);
    tableWidget->setParent(this);
    tableWidget->move(this->width()*0.2,this->height()*0.4);
    tableWidget->setShowGrid(false);

    //设置表头
    QStringList header;
    header<<"药物种类"<<"药物质量/g"<<"剂数";
    tableWidget->setHorizontalHeaderLabels(header);
    //取消表格中的线
    tableWidget->setShowGrid(false);
    //设置表头高度
    tableWidget->horizontalHeader()->setFixedHeight(60);



    //设置自适应等宽和自动等宽
    QHeaderView* headerView = tableWidget->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);


    MyPushButton *analysisMedicine = new MyPushButton;
    analysisMedicine->setFixedSize(120,55);
    analysisMedicine->move(this->width()*0.75,this->height()*0.5);
    analysisMedicine->setParent(this);
    analysisMedicine->setStyleSheet("background:rgb(20,255,150);border-radius:10px;padding:2px 4px;");
    analysisMedicine->setText("我的体质分析");

    QProgressBar *analysisBar = new QProgressBar;
    analysisBar->setParent(this);
    analysisBar->setRange(0,1000);
    analysisBar->setFixedSize(120,55);
    analysisBar->move(this->width()*0.85,this->height()*0.5);
    analysisBar->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{border-radius:5px;background:blue}");
    analysisBar->setValue(1);


    //按键读取药方
    connect(readMedicine,&MyPushButton::clicked,[=](){
        readMedicine->zoom1();
        readMedicine->zoom2();
        readMedicineTxt(tableWidget,dirpathMedicine);
        qDebug()<<"评分1"<<composit_score[0];
        qDebug()<<"评分2"<<composit_score[1];
        qDebug()<<"评分3"<<composit_score[2];
        qDebug()<<"评分4"<<composit_score[3];


    });

    //对药物进行分析
    connect(analysisMedicine,&MyPushButton::clicked,[=](){
        analysisMedicine->zoom1();
        analysisMedicine->zoom2();
        QTimer::singleShot(500,this,[=](){

            for(int i=0;i<1000;i++)
            {
                analysisBar->setValue(i+1);
                Sleep(5);
                if(i%100==0)
                    qDebug()<<i;
            }

            analysis *analysisWidget = new analysis;
            this->hide();
            analysisWidget->setGeometry(this->geometry());  //保证新老界面维持在同一个位置
            analysisWidget->show();
            analysisWidget->setFixedSize(1600,900);

            connect(analysisWidget,&analysis::analysisBck,[=](){
                QTimer::singleShot(200,this,[=](){

                    this->setGeometry(analysisWidget->geometry());  //保证新老界面维持在同一个位置
                    this->show();
                    analysisWidget->hide();
                    delete analysisWidget;
                });
            });
        });

    });

    clientBackButton *clientBckBtn = new clientBackButton(":/res1/clientback.png");
    clientBckBtn->setParent(this);
    clientBckBtn->move(this->width()*0.75,this->height()*0.8);

    //返回登陆界面
    connect(clientBckBtn,&clientBackButton::clicked,[=](){
        clientBckBtn->zoom1();
        clientBckBtn->zoom2();

        QTimer::singleShot(300,this,[=](){
        emit this->chooseSceneBack();
        emit this->chooseSceneBackFace();
        });

    });

    serial = new QSerialPort(this);
    serialportMedicineOpen();  //寻找串口
    //设置取药按钮
    MyPushButton *getMedicine = new MyPushButton;
    getMedicine->setFixedSize(120,55);
    getMedicine->move(this->width()*0.75,this->height()*0.4);
    getMedicine->setParent(this);
    getMedicine->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");
    getMedicine->setText("自动取药");

    connect(getMedicine,&MyPushButton::clicked,[=](){
        getMedicine->zoom1();
        getMedicine->zoom2();
        QTimer::singleShot(500,this,[=](){
            serialportWrite(serial);
        });
    });

    connect(serial, SIGNAL(readyRead()), this, SLOT(on_SerialPort_readyRead()));

}

void clientScene::readMedicineTxt(QTableWidget *tableWidget,QString dirpath)
{
    QFile medicineTxt(dirpath);
    QTextStream medicineTxtStream(&medicineTxt);  //数据流
    QString QStrLine[10];

    if(!medicineTxt.open(QIODevice::ReadOnly|QIODevice::Text)) //打开文件
    {
        QMessageBox about;
        about.setText(tr("目前没有药方"));
        about.exec();
        return;
    }

    int i=0;
    QString medicineNameEach;  //药物名称
    QString medicineQualityEach; //药物质量
    int medicineRowCount; //记录当前行数
    while(!medicineTxtStream.atEnd())
    {
        QByteArray Line=medicineTxt.readLine();
        QStrLine[i]=Line;
        //qDebug()<<"QStrLine[i]:"<<QStrLine[i];
        //提取数字和名字

        for(int j=0;j<QStrLine[i].length();j++)
        {
            if(QStrLine[i][0] == '@')  //读取药物编码
            {
                for(int k=1;k<QStrLine[i].length();k++)
                {
                    serialportString.append(QStrLine[i][k]);
                }
                serialportString.chop(1);  //去掉换行符
                qDebug()<<"读取的药物信息" + serialportString;
                sendBuffer[numSend] = serialportString.toLatin1();
                serialportString.clear();
                numSend++;
                break;
            }
            else if(QStrLine[i][0] == '*')  //读取剂数
            {
                for(int k=1;k<QStrLine[i].length();k++)
                {
                    serialportString.append(QStrLine[i][k]);
                }
                qDebug()<<"读取的药物信息" + serialportString;
                sendBuffer[numSend] = serialportString.toLatin1();
                serialportString.clear();
                break;
            }
            else if(QStrLine[i][j]>='0'&& QStrLine[i][j]<='9')
            {
                medicineQualityEach.append(QStrLine[i][j]);
            }
            else if(QStrLine[i][j]!=' '&& (QStrLine[i][j]<'0' || QStrLine[i][j]>'9'))
            {
                medicineNameEach.append(QStrLine[i][j]);
            }
        }

        if(medicineNameEach == "剂数\n")  //写入剂数
        {
            //向tableWidget中写入内容
            tableWidget->setItem(0,2,new QTableWidgetItem(medicineQualityEach));

            //设置表格内容居中
            tableWidget->item(0,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        }
        else if(medicineNameEach != "剂数\n" && medicineNameEach != "")//写入药物名称和质量
        {
            medicineRowCount = tableWidget->rowCount();
            tableWidget->insertRow(medicineRowCount);  //插入新行

            //向tableWidget中写入内容
            tableWidget->setItem(i,0,new QTableWidgetItem(medicineNameEach));
            tableWidget->setItem(i,1,new QTableWidgetItem(medicineQualityEach));

            get_composit(medicineNameEach,composit_score);

            //设置表格内容居中
            tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

            medicineNameEach.clear();
            medicineQualityEach.clear();

            //合并剂数列单元格
            tableWidget->setSpan(0,2,i+1,2);

            i++;
        }

    }
    medicineTxt.close();
}

//串口通信
void clientScene::serialportMedicineOpen()
{
    //扫描串口
    foreach(const QSerialPortInfo &Info,QSerialPortInfo ::availablePorts())
        {
            QSerialPort CurrentPort;
            CurrentPort.setPort(Info);
            if(CurrentPort.open(QIODevice::ReadWrite))
            {
                qDebug()<<"port:" + CurrentPort.portName() + "扫描成功";
                portName = CurrentPort.portName();
                CurrentPort.close();   //先开再关，把串口名称先导入
            }
        }
}

//打开串口并写入消息
void clientScene::serialportWrite(QSerialPort *serial)
{

    serial->setPortName(portName);  //设置串口名称
    if(serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口";
    }

    serial->setBaudRate(QSerialPort::Baud9600);  //设置波特率
    serial->setDataBits(QSerialPort::Data8);  //设置数据位
    serial->setParity(QSerialPort::NoParity);  //设置是否奇偶校验
    serial->setStopBits(QSerialPort::OneStop);  //设置停止位
    serial->setFlowControl(QSerialPort::NoFlowControl);  //设置是否流控制
    serial->setDataTerminalReady(false);
    serial->setRequestToSend(false);

    //扫描发现串口后，开始进行设置


    for(int i=0;i<numSend+1;i++)   //必须有最后一步的"n8\n"的换行符才能触发MCU的串口中断
    {

        serial->write(sendBuffer[i]);
        qDebug()<<sendBuffer[i];
        Sleep(1000);
    }

    qDebug()<<"写入语句";

}

void clientScene::on_SerialPort_readyRead()  //读取串口数据
{
    if(serial->isOpen())
    {
        QByteArray recvData = serial->readAll();
        QString readData;
        readData.prepend(recvData);
        qDebug() <<"接收：" + QString(readData);
    }
}


void clientScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res1/clientScene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void clientScene::get_composit(QString medicine,int (&composit_score)[4])
{
    if((medicine == "附子\n")||(medicine == "干姜\n")||(medicine == "肉桂\n")||(medicine == "丁香\n")||(medicine == "茴香\n")||(medicine == "茱萸\n")||(medicine == "杜仲\n"))
        {composit_score[0]++;}
    else if((medicine == "鱼腥草\n")||(medicine == "金银花\n")||(medicine == "菊花\n")||(medicine == "夏枯草\n")||(medicine == "连翘\n")||(medicine == "薄荷\n")||(medicine == "冰片\n"))
        {composit_score[1]++;}
    else if((medicine == "茨实\n")||(medicine == "茯苓\n")||(medicine == "山药\n")||(medicine == "薏仁\n")||(medicine == "苍术\n")||(medicine == "藿香\n"))
        {composit_score[2]++;}
    else if((medicine == "川贝母\n")||(medicine == "麻黄\n")||(medicine == "蛇床子\n")||(medicine == "半夏\n")||(medicine == "黄柏\n"))
        {composit_score[3]++;}
}

clientScene::~clientScene()
{
    serial->setPortName(portName);
    serial->close();
    numSend = 0;
    composit_score[0] = 0;
    composit_score[1] = 0;
    composit_score[2] = 0;
    composit_score[3] = 0;
    delete serial;
}
