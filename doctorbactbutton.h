#ifndef DOCTORBACTBUTTON_H
#define DOCTORBACTBUTTON_H

#include <QPushButton>

class doctorBactButton:public QPushButton
{
    Q_OBJECT
public:
    doctorBactButton(QString doctorBackBtnPath);
    QString doctorBackBtnPath;
    void zoom1();
    void zoom2();
};

#endif // DOCTORBACTBUTTON_H
