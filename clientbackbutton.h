#ifndef CLIENTBACKBUTTON_H
#define CLIENTBACKBUTTON_H

#include <QPushButton>

class clientBackButton:public QPushButton
{
    Q_OBJECT
public:
    clientBackButton(QString clientBackBtnPath);
    QString clientBackBtnPath;
    void zoom1();
    void zoom2();
};

#endif // CLIENTBACKBUTTON_H
