#include "registerscene.h"
#include "mypushbutton.h"
#include "opencvscene.h"
#include <QDir>
#include <QPaintEvent>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QComboBox>
#include <QFile>

QString IDstring;
QString IDSend;

registerScene::registerScene()
{
    this->setFixedSize(1600,900);

    QFont font2;
    font2.setPointSize(23);
    font2.setFamily("黑体");

    QLineEdit *lineEditID_new = new QLineEdit;
    lineEditID_new->setParent(this);
    lineEditID_new->move(this->width()*0.65,this->height()*0.3);
    lineEditID_new->setMinimumWidth(400);
    lineEditID_new->setMinimumHeight(50);
    lineEditID_new->setMaxLength(400);
    QLabel *ID_new_Label = new QLabel;
    ID_new_Label->setParent(this);
    font2.setPointSize(15);
    ID_new_Label->setFont(font2);
    ID_new_Label->setText(QString("账号"));
    ID_new_Label->setGeometry(QRect(this->width()*0.65-120,this->height()*0.3,120,50));

    QLineEdit *lineEditPass_new = new QLineEdit;
    lineEditPass_new->setParent(this);
    lineEditPass_new->move(this->width()*0.65,this->height()*0.4);
    lineEditPass_new->setMinimumWidth(400);
    lineEditPass_new->setMinimumHeight(50);
    lineEditPass_new->setMaxLength(400);
    QLabel *Pass_new_Label = new QLabel;
    Pass_new_Label->setParent(this);
    Pass_new_Label->setFont(font2);
    Pass_new_Label->setText(QString("密码"));
    Pass_new_Label->setGeometry(QRect(this->width()*0.65-120,this->height()*0.4,120,50));

    QLineEdit *lineEditName_new = new QLineEdit;
    lineEditName_new->setParent(this);
    lineEditName_new->move(this->width()*0.65,this->height()*0.5);
    lineEditName_new->setMinimumWidth(400);
    lineEditName_new->setMinimumHeight(50);
    lineEditName_new->setMaxLength(400);
    QLabel *Name_new_Label = new QLabel;
    Name_new_Label->setParent(this);
    Name_new_Label->setFont(font2);
    Name_new_Label->setText(QString("姓名"));
    Name_new_Label->setGeometry(QRect(this->width()*0.65-120,this->height()*0.5,120,50));

    QComboBox *sexBox = new QComboBox;
    sexBox->setParent(this);
    sexBox->addItem("男");
    sexBox->addItem("女");
    sexBox->move(this->width()*0.65,this->height()*0.6);
    sexBox->setFixedSize(70,50);
    QLabel *Sex_new_Label = new QLabel;
    Sex_new_Label->setParent(this);
    Sex_new_Label->setFont(font2);
    Sex_new_Label->setText(QString("性别"));
    Sex_new_Label->setGeometry(QRect(this->width()*0.65-120,this->height()*0.6,120,50));

    QLineEdit *lineEditAge_new = new QLineEdit;
    lineEditAge_new->setParent(this);
    lineEditAge_new->move(this->width()*0.8,this->height()*0.6);
    lineEditAge_new->setMinimumWidth(55);
    lineEditAge_new->setMinimumHeight(50);
    lineEditAge_new->setMaxLength(400);
    QLabel *Age_new_Label = new QLabel;
    Age_new_Label->setParent(this);
    Age_new_Label->setFont(font2);
    Age_new_Label->setText(QString("年龄"));
    Age_new_Label->setGeometry(QRect(this->width()*0.8-70,this->height()*0.6,80,50));

    //创建确认按钮
    MyPushButton *backMainBtn = new MyPushButton;
    backMainBtn->setParent(this);
    backMainBtn->move(this->width()*0.6,this->height()*0.8);
    backMainBtn->setFixedSize(120,60);
    backMainBtn->setText("确认");



    //点击确认按钮，记录注册信息并返回登陆界面
    connect(backMainBtn,&MyPushButton::clicked,[=](){

        //记录用户填写的注册信息
        QString idString = lineEditID_new->text();
        QString passString = lineEditPass_new->text();
        QString nameString = lineEditName_new->text();
        QString ageString = lineEditAge_new->text();
        QString sexString = sexBox->currentText();


        QString dirPath;
        dirPath = QString("AllData") + QString("/") + idString;
        QFile passFile(dirPath + QString("/pass.txt"));
        QFile nameFile(dirPath + QString("/name.txt"));
        QFile sexFile(dirPath + QString("/sex.txt"));
        QFile ageFile(dirPath + QString("/age.txt"));

        IDSend = idString;  //传给widget作为文件传输

        //创建以用户ID为文件夹名的文件夹
        QDir dir;
        if(!dir.exists(dirPath))
        {
            dir.mkpath(dirPath);
        }

        //创建并写入pass文本文档
        passFile.open( QIODevice::WriteOnly);
        passFile.write(passString.toUtf8());
        passFile.close();

        //创建并写入name文本文档
        nameFile.open( QIODevice::WriteOnly);
        nameFile.write(nameString.toUtf8());
        nameFile.close();

        //创建并写入sex文本文档
        sexFile.open( QIODevice::WriteOnly);
        sexFile.write(sexString.toUtf8());
        sexFile.close();

        //创建并写入age文本文档
        ageFile.open( QIODevice::WriteOnly);
        ageFile.write(ageString.toUtf8());
        ageFile.close();

        QTimer::singleShot(500,this,[=](){
        emit this->sendFileToClient();
        emit this->chooseSceneBack();
        });
    });

    //创建人脸识别按钮
    MyPushButton *opencvbtn = new MyPushButton;
    opencvbtn->setParent(this);
    opencvbtn->move(this->width()*0.8,this->height()*0.8);
    opencvbtn->setFixedSize(120,60);
    opencvbtn->setText("人脸注册");

    connect(opencvbtn,&MyPushButton::clicked,[=](){
        
        IDstring = lineEditID_new->text();
        opencvScene *opencvwidget = new opencvScene;   //人脸注册界面
        this->hide();
        opencvwidget->setGeometry(this->geometry());
        opencvwidget->setFixedSize(1600,900);
        opencvwidget->setWindowTitle("人脸注册界面");
        opencvwidget->show(); 
        
        //监听从opencv拍摄界面传来的消息
        connect(opencvwidget,&opencvScene::opencvBckBtn,this,[=](){
            this->show();
            opencvwidget->hide();
            this->setGeometry(opencvwidget->geometry());
            delete opencvwidget;
        });

    });
}

void registerScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res1/registerscene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
