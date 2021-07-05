#include "mypushbutton.h"
#include <QPropertyAnimation>

MyPushButton::MyPushButton()
{

}


void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);  //时间间隔
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));  //起始位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //终止位置
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //开始执行
}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);  //时间间隔
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));  //终止位置
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //开始执行
}
