#include "registerbutton.h"
#include <QDebug>
#include <QString>
#include <QPropertyAnimation>
registerButton::registerButton(QString registerPath)
{
    registerButtonPath = registerPath;  //按钮图片路径
    QPixmap pixmap;
    bool ret = pixmap.load(registerButtonPath);
    if(!ret)
    {
        qDebug()<<registerPath<<"加载图片失败！";
    }

    //设置图片尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片样式表
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width()*0.8,pixmap.height()*0.8));
}

void registerButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);  //时间间隔
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));  //起始位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //终止位置
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //开始执行
}

void registerButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);  //时间间隔
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));  //终止位置
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //开始执行
}
