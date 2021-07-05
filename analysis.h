#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QWidget>

class analysis:public QWidget
{
    Q_OBJECT
public:
    explicit analysis();
    void paintEvent(QPaintEvent *);  //重写paintEvent事件
signals:
    void analysisBck(void);
};

#endif // ANALYSIS_H
