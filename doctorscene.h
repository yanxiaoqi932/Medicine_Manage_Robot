#ifndef DOCTORSCENE_H
#define DOCTORSCENE_H

#include <QWidget>
#include <QTableWidget>

class doctorScene:public QWidget
{
    Q_OBJECT
public:
    explicit doctorScene();

    void paintEvent(QPaintEvent *);  //重写paintEvent事件
    void on_saveDataBtn_clicked(QTableWidget *tableWidget,QString dirpath);
    void saveMedicineTxt(QTableWidget *tableWidget,QString dirpath);
    int getMedicineIndex(QString medicineName);
    //int hot;  int cold;  int humid;  int dry;
signals:
    void doctorSceneBack(void);
};

#endif // DOCTORSCENE_H
