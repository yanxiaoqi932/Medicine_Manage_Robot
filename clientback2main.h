#ifndef CLIENTBACK2MAIN_H
#define CLIENTBACK2MAIN_H

#include <QPushButton>
class clientBack2Main:public QPushButton
{
    Q_OBJECT
public:
    clientBack2Main(QString backButtonPath);
    QString backButtonPath;
    void zoom1();
    void zoom2();
};

#endif // CLIENTBACK2MAIN_H
