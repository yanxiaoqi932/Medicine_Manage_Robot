#ifndef LOADBUTTON_H
#define LOADBUTTON_H
#include <QPushButton>


class loadbutton : public QPushButton
{
    Q_OBJECT
public:
    loadbutton(QString loadButtonpPath);
    QString loadButtonPath;
    void zoom1();
    void zoom2();
signals:

public slots:

};

#endif // LOADBUTTON_H
