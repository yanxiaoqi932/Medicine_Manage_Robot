#ifndef REGISTERSCENE_H
#define REGISTERSCENE_H

#include <QWidget>

class registerScene:public QWidget
{
    Q_OBJECT
public:
    explicit registerScene();

    void paintEvent(QPaintEvent *);  //重写paintEvent事件

signals:
    void chooseSceneBack(void);
    void sendFileToClient(void);
};

#endif // REGISTERSCENE_H
