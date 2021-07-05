#ifndef REGISTERBUTTON_H
#define REGISTERBUTTON_H

#include <QPushButton>

class registerButton : public QPushButton
{
    Q_OBJECT
public:
    registerButton(QString registerButtonPath);
    QString registerButtonPath;
    void zoom1();
    void zoom2();
signals:

public slots:
};

#endif // REGISTERBUTTON_H
