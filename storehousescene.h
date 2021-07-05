#ifndef STOREHOUSESCENE_H
#define STOREHOUSESCENE_H

#include <QWidget>
#include <QtSerialPort>

class storehouseScene:public QWidget
{
    Q_OBJECT
public:
    explicit storehouseScene();
    ~storehouseScene();
    void serialportMedicineOpen();
    QWidget *widget;
signals:
    void storeBck(void);
private:
    QSerialPort *serial2;
private slots:
    void serialportRead(QSerialPort *serial2);
    void on_SerialPort_readyRead2(void);
};

#endif // STOREHOUSESCENE_H
