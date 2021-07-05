#include "analysis.h"
#include "clientscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QListWidget>

extern int composit_score[4];
extern QByteArray name,sex,age;
analysis::analysis()
{
    this->setFixedSize(1600,900);

    qDebug()<<composit_score[0];
    qDebug()<<composit_score[1];
    qDebug()<<composit_score[2];
    qDebug()<<composit_score[3];

    //用户姓名栏
    QFont font2;
    font2.setPointSize(15);
    font2.setFamily("黑体");

    QLabel *nameEdit = new QLabel;
    nameEdit->setParent(this);
    nameEdit->setFixedSize(120,45);
    nameEdit->move(this->width()*0.3,this->height()*0.2);
    nameEdit->setFont(font2);
    nameEdit->setText(name);
    QLabel *namelabel = new QLabel;
    namelabel->setParent(this);
    font2.setPointSize(15);
    namelabel->setFont(font2);
    namelabel->setText(QString("姓名："));
    namelabel->setGeometry(QRect(this->width()*0.3-70,this->height()*0.2-5,120,50));

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
    ageEdit->move(this->width()*0.7,this->height()*0.2);
    ageEdit->setFont(font2);
    ageEdit->setText(age);
    QLabel *agelabel = new QLabel;
    agelabel->setParent(this);
    font2.setPointSize(15);
    agelabel->setFont(font2);
    agelabel->setText(QString("年龄："));
    agelabel->setGeometry(QRect(this->width()*0.7-70,this->height()*0.2-5,120,50));

    //返回按钮
    MyPushButton *analysisBck = new MyPushButton;
    analysisBck->setParent(this);
    analysisBck->resize(120,75);
    analysisBck->move(this->width()*0.7,this->height()*0.8);
    analysisBck->setText("返回");
    analysisBck->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    QLabel *physique = new QLabel;
    physique->setParent(this);
    physique->move(this->width()*0.3,this->height()*0.3);
    font2.setPointSize(17);
    font2.setFamily("华文新魏");
    physique->setFont(font2);


    QTextEdit *suggest = new QTextEdit;
    suggest->setParent(this);
    font2.setPointSize(17);
    font2.setFamily("华文新魏");
    suggest->setFont(font2);
    suggest->move(this->width()*0.3,this->height()*0.35);
    suggest->setMinimumWidth(600);
    suggest->setMinimumHeight(500);
    suggest->setFrameShape(QListWidget::NoFrame);

    QString dirpath = "AllData";
    QFile analy_1_File(dirpath + QString("/analy_1.txt"));
    QFile analy_2_File(dirpath + QString("/analy_2.txt"));
    QFile analy_3_File(dirpath + QString("/analy_3.txt"));
    QFile analy_4_File(dirpath + QString("/analy_4.txt"));
    QString analy_1,analy_2,analy_3,analy_4;





    if(composit_score[0]>composit_score[1] || composit_score[2]>composit_score[3])
    {
        if(analy_1_File.open(QIODevice::ReadOnly))
        {
            analy_1 = analy_1_File.readAll();
            analy_1_File.close();
        }
        physique->setText("体质判断：湿寒体质");
        suggest->setText(analy_1);
    }

    else if(composit_score[0]>composit_score[1] || composit_score[2]<composit_score[3])
    {
        if(analy_2_File.open(QIODevice::ReadOnly))
        {
            analy_2 = analy_2_File.readAll();
            analy_2_File.close();
        }
        physique->setText("体质判断：燥寒体质");
        suggest->setText(analy_2);
    }

    else if(composit_score[0]<composit_score[1] || composit_score[2]>composit_score[3])
    {
        if(analy_3_File.open(QIODevice::ReadOnly))
        {
            analy_3 = analy_3_File.readAll();
            analy_3_File.close();
        }
        physique->setText("体质判断：燥热体质");
        suggest->setText(analy_3);
    }

    else if(composit_score[0]<composit_score[1] || composit_score[2]<composit_score[3])
    {
        if(analy_4_File.open(QIODevice::ReadOnly))
        {
            analy_4 = analy_4_File.readAll();
            analy_4_File.close();
        }
        physique->setText("体质判断：湿热体质");
        suggest->setText(analy_4);
    }

    connect(analysisBck,&MyPushButton::clicked,[=](){
        analysisBck->zoom1();
        analysisBck->zoom2();
        QTimer::singleShot(200,this,[=](){
            emit this->analysisBck();
        });

    });



}

void analysis::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res1/clientScene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
