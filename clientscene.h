#ifndef CLIENTSCENE_H
#define CLIENTSCENE_H

#include <QWidget>
#include <QTableWidget>
#include <QtSerialPort>
class clientScene:public QWidget
{
    Q_OBJECT
public:
    explicit clientScene();
    void paintEvent(QPaintEvent *);  //重写paintEvent事件
    void readMedicineTxt(QTableWidget *tableWidget,QString dirpath);  //读取txt文档
    void serialportMedicineOpen();
    void get_composit(QString medicine,int (&composit_score)[4]);
    ~clientScene();

    int hot;    int cold;   int moist;  int dry;
signals:
    void chooseSceneBack(void);
    void chooseSceneBackFace(void);
private:
    QSerialPort *serial;

private slots:
    void on_SerialPort_readyRead(void);
    void serialportWrite(QSerialPort *serial);


};

#endif // CLIENTSCENE_H
