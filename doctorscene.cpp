#include "doctorscene.h"
#include "mypushbutton.h"
#include "opencvscene.h"
#include "doctorbactbutton.h"
#include "storehousescene.h"
#include <QDir>
#include <QPaintEvent>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QComboBox>
#include <QFile>
#include <QCompleter>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItem>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QAxObject>
#include <QMessageBox>
doctorScene::doctorScene()
{
    this->setFixedSize(1600,900);

    QFont font2;
    font2.setPointSize(15);
    font2.setFamily("黑体");

    //输入患者编号
    QLineEdit *patientIDLine = new QLineEdit;
    patientIDLine->setParent(this);
    patientIDLine->move(this->width()*0.2,this->height()*0.2);
    patientIDLine->setMinimumWidth(50);
    patientIDLine->setMaxLength(100);
    patientIDLine->setFont(font2);

    QLabel *patientIDLabel = new QLabel;
    patientIDLabel->setParent(this);
    patientIDLabel->setFont(font2);
    font2.setPointSize(15);
    font2.setFamily("华文新魏");
    patientIDLabel->setStyleSheet("color:blue;");
    patientIDLabel->setText("请输入患者编号：");
    patientIDLabel->move(this->width()*0.2-200,this->height()*0.2);

    MyPushButton *findPatient = new MyPushButton;
    findPatient->setParent(this);
    findPatient->setFixedSize(75,35);
    findPatient->move(this->width()*0.2+300,this->height()*0.2);
    findPatient->setText("查询");
    findPatient->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    //患者姓名
    QLabel *label_name_edit = new QLabel;
    label_name_edit->setParent(this);
    label_name_edit->setFont(font2);
    label_name_edit->move(this->width()*0.12,this->height()*0.3);
    label_name_edit->setFixedSize(120,45);

    QLabel *label_name = new QLabel;
    label_name->setParent(this);
    label_name->setFont(font2);
    label_name->move(this->width()*0.2,this->height()*0.3);
    label_name->setFixedSize(120,45);

    //患者性别
    QLabel *label_sex_edit = new QLabel;
    label_sex_edit->setParent(this);
    label_sex_edit->setFont(font2);
    label_sex_edit->move(this->width()*0.27,this->height()*0.3);
    label_sex_edit->setFixedSize(120,45);

    QLabel *label_sex = new QLabel;
    label_sex->setParent(this);
    label_sex->setFont(font2);
    label_sex->move(this->width()*0.31,this->height()*0.3);
    label_sex->setFixedSize(120,45);

    //患者年龄
    QLabel *label_age_edit = new QLabel;
    label_age_edit->setParent(this);
    label_age_edit->setFont(font2);
    label_age_edit->move(this->width()*0.34,this->height()*0.3);
    label_age_edit->setFixedSize(120,45);

    QLabel *label_age = new QLabel;
    label_age->setParent(this);
    label_age->setFont(font2);
    label_age->move(this->width()*0.38,this->height()*0.3);
    label_age->setFixedSize(120,45);

    //点击查询键后得到患者信息
    connect(findPatient,&MyPushButton::clicked,[=](){
        findPatient->zoom1();
        findPatient->zoom2();

        QTimer::singleShot(500,this,[=](){
            QString name,sex,age;  //患者各类信息
            QString patientID = patientIDLine->text(); //患者ID
            QString dirpath = "AllData/" + patientID;
            QFile nameFile(dirpath + QString("/name.txt"));
            QFile sexFile(dirpath + QString("/sex.txt"));
            QFile ageFile(dirpath + QString("/age.txt"));

            if(nameFile.open(QIODevice::ReadOnly))
            {
                name = nameFile.readAll();
                nameFile.close();
            }

            //读取客户性别
            if(sexFile.open(QIODevice::ReadOnly))
            {
                sex = sexFile.readAll();
                sexFile.close();
            }

            //读取客户年龄
            if(ageFile.open(QIODevice::ReadOnly))
            {
                age = ageFile.readAll();
                ageFile.close();
            }

            //输出患者姓名
            label_name->setText(QString(name));
            label_name_edit->setText("患者姓名：");

            //输出患者性别
            label_sex->setText(QString(sex));
            label_sex_edit->setText("性别");

            //输出患者年龄
            label_age->setText(QString(age));
            label_age_edit->setText("年龄");
        });
    });

    //设置退出按钮
    doctorBactButton *dctBckBtn = new doctorBactButton(":/res1/clientback.png");
    dctBckBtn->setParent(this);
    dctBckBtn->move(this->width()*0.8,this->height()*0.8-25);

    connect(dctBckBtn,&doctorBactButton::clicked,[=](){
        dctBckBtn->zoom1();
        dctBckBtn->zoom2();

        QTimer::singleShot(300,this,[=](){
        emit this->doctorSceneBack();
        });

    });

    //设置药库查询按钮
    MyPushButton *storehouseBtn = new MyPushButton;
    storehouseBtn->setParent(this);
    storehouseBtn->move(this->width()*0.82,this->height()*0.7-25);
    storehouseBtn->setFixedSize(185,65);
    storehouseBtn->setText("药库状态查询");
    storehouseBtn->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    connect(storehouseBtn,&MyPushButton::clicked,[=](){
        storehouseBtn->zoom1();
        storehouseBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            storehouseScene *storeWidget = new storehouseScene;
            this->hide();
            storeWidget->setGeometry(this->geometry());  //保证新老界面维持在同一个位置
            storeWidget->show();
            storeWidget->setFixedSize(1600,900);

            //监听storehousebtn的返回消息
            connect(storeWidget,&storehouseScene::storeBck,[=](){
                storehouseBtn->zoom1();
                storehouseBtn->zoom2();

                QTimer::singleShot(200,this,[=](){
                    this->setGeometry(storeWidget->geometry());  //保证新老界面维持在同一个位置
                    this->show();
                    storeWidget->hide();
                    delete storeWidget;
                });
            });
        });
    });

    //医生开药
        //标题
//    QLabel *labelMedicine = new QLabel;
//    font2.setPointSize(20);
//    labelMedicine->setFont(font2);
//    labelMedicine->move(this->width()*0.7,this->height()*0.12);
//    labelMedicine->setParent(this);
//    labelMedicine->setText("开药区");

        //输入框
    QLabel *labelMedicineWhich = new QLabel;
    font2.setPointSize(15);
    labelMedicineWhich->setFont(font2);
    labelMedicineWhich->move(this->width()*0.55,this->height()*0.2+10);
    labelMedicineWhich->setParent(this);
    labelMedicineWhich->setText("种类");

    QLineEdit *medicineLine = new QLineEdit;
    medicineLine->setParent(this);
    medicineLine->move(this->width()*0.6,this->height()*0.2);
    medicineLine->setPlaceholderText("查找药物");
    medicineLine->setFixedSize(160,45);

        //模糊查询对象
    QStringList word_list;
    word_list<<"附子"<<"干姜"<<"肉桂"<<"丁香"<<"茴香"<<"茱萸"<<"杜仲"<<"鱼腥草"<<"金银花"<<"菊花"<<"夏枯草"<<"连翘"<<"薄荷"<<"冰片"<<"茨实"<<"茯苓"<<"山药"<<"赤小豆"<<"薏仁"<<"苍术"<<"藿香"<<"麻黄"<<"蛇床子"<<"半夏"<<"黄柏"<<"川贝母";
    QCompleter *MyInfor = new QCompleter(word_list);

        //设置edit的模糊查询对象
    medicineLine->setCompleter(MyInfor);

        //输入药量
    QLabel *labelMedicineQuality = new QLabel;
    labelMedicineQuality->setFont(font2);
    font2.setPointSize(15);
    labelMedicineQuality->move(this->width()*0.72,this->height()*0.2+10);
    labelMedicineQuality->setParent(this);
    labelMedicineQuality->setText("质量");

    QLineEdit *medicineQualityLine = new QLineEdit;
    medicineQualityLine->setParent(this);
    medicineQualityLine->move(this->width()*0.77,this->height()*0.2);
    medicineQualityLine->setFixedSize(100,45);

        //输入剂量
    QLabel *labelMedicineDosage = new QLabel;
    labelMedicineDosage->setFont(font2);
    font2.setPointSize(15);
    labelMedicineDosage->move(this->width()*0.55,this->height()*0.28+10);
    labelMedicineDosage->setParent(this);
    labelMedicineDosage->setText("剂数");

    QLineEdit *dosageMedicine = new QLineEdit;
    dosageMedicine->setParent(this);
    dosageMedicine->move(this->width()*0.6,this->height()*0.28);
    dosageMedicine->setFixedSize(160,45);

        //确认按钮
    MyPushButton *medicineAssign = new MyPushButton;
    medicineAssign->setParent(this);
    medicineAssign->move(this->width()*0.87,this->height()*0.2-5);
    medicineAssign->setText("确认");
    medicineAssign->setFixedSize(70,45);
    medicineAssign->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

        //开药完成按钮
    MyPushButton *medicineEnd = new MyPushButton;
    medicineEnd->setParent(this);
    medicineEnd->move(this->width()*0.72,this->height()*0.28);
    medicineEnd->setText("开药完成");
    medicineEnd->setFixedSize(312,45);
    medicineEnd->setStyleSheet("background:rgb(135,206,235);border-radius:10px;padding:2px 4px;");

    QTableWidget *tableWidget = new QTableWidget(0,4);  //注意，此处的行不包括表头！
    tableWidget->resize(650,450);
    font2.setPointSize(15);
    font2.setFamily("宋体");
    tableWidget->setFont(font2);
    tableWidget->setWindowTitle("QTableWidget & Item");
    tableWidget->setParent(this);
    tableWidget->move(this->width()*0.2-200,this->height()*0.35);
    //设置表头
    QStringList header;
    header<<"药物编号"<<"药物种类"<<"药物质量/g"<<"剂数";
    tableWidget->setHorizontalHeaderLabels(header);
    //取消表格中的线
    tableWidget->setShowGrid(false);
    //设置表头高度
    tableWidget->horizontalHeader()->setFixedHeight(60);

    //设置自适应等宽和自动等宽
    QHeaderView* headerView = tableWidget->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);

    //逐个输出药物
    static int numMedicine = 0;

    //将药物种类和数量，编号，剂数填入表格中
    connect(medicineAssign,&MyPushButton::clicked,[=](){
        medicineAssign->zoom1();
        medicineAssign->zoom2();

        QTimer::singleShot(500,this,[=](){
            QString medicineName,medicineQulity,medicineDosage;
            medicineName = medicineLine->text();
            medicineQulity = medicineQualityLine->text();
            medicineDosage = dosageMedicine->text();

            int indexMedicine;  //记录药物索引

            if(medicineDosage == "")
            {
                QString medicineNameReal = medicineName;
                QString medicineQulityReal = medicineQulity;

                //获取药物索引
                indexMedicine =  getMedicineIndex(medicineNameReal);
                QString stingIndexMeicine = QString::number(indexMedicine);

                int medicineRowCount;
                medicineRowCount = tableWidget->rowCount();
                tableWidget->insertRow(medicineRowCount);  //插入新行
                //设置表格内容
                tableWidget->setItem(numMedicine,0,new QTableWidgetItem(stingIndexMeicine));
                tableWidget->setItem(numMedicine,1,new QTableWidgetItem(medicineNameReal));
                tableWidget->setItem(numMedicine,2,new QTableWidgetItem(medicineQulityReal));

                //设置表格内容居中
                tableWidget->item(numMedicine,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                tableWidget->item(numMedicine,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                tableWidget->item(numMedicine,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                tableWidget->setSpan(0,3,numMedicine+1,2);  //合并剂数列单元格

                numMedicine++;
                medicineLine->clear();
                medicineQualityLine->clear();
            }

            else    //写入剂数
            {
                //设置表格内容
                tableWidget->setItem(0,3,new QTableWidgetItem(medicineDosage));
                //设置表格内容居中
                tableWidget->item(0,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                dosageMedicine->clear();
            }

        });
    });


    connect(medicineEnd,&MyPushButton::clicked,[=](){
        medicineEnd->zoom1();
        medicineEnd->zoom2();

        QTimer::singleShot(500,this,[=](){
            numMedicine = 0;
            QString patientID = patientIDLine->text(); //患者ID
            QString dirpath = "AllData/" + patientID;
            //保存表格文件为txt格式
            saveMedicineTxt(tableWidget,dirpath);
        });
    });

}

void doctorScene::saveMedicineTxt(QTableWidget *tableWidget,QString dirpath)
{
    int row = tableWidget->rowCount(); //行数

    QFile medicineFile(dirpath + QString("/medicine.txt"));  //创建名称为medicine.txt的文档
    medicineFile.open(QIODevice::Text|QIODevice::WriteOnly); //加入QIODevice::Text才能换行

    QString medicineContent;
    QTextStream medicineContentStream(&medicineFile);  //文件输入流
    medicineContentStream.setCodec("UTF-8");

    //向txt文档中写入药物名称和质量
    for(int i=0;i<row;i++)
    {
        for(int j=1;j<3;j++)
        {
            medicineContent.append(tableWidget->item(i,j)->text());
        }
        medicineContentStream<<medicineContent<<endl;
        medicineContent.clear();
    }

    //向txt文档中写入剂数
    medicineContent.append("剂数");
    medicineContent.append(tableWidget->item(0,3)->text());
    qDebug()<<medicineContent;
    medicineContentStream<<medicineContent<<endl;
    medicineContent.clear();

    //向txt文档中写入串口通信语句:  "@编号1*质量1/编号2*质量2/.../#剂数"

    for(int i=0;i<row;i++)
    {
        medicineContent.append("@");
        for(int j=0;j<3;j+=2)
        {
            if(j==0)
            {
                medicineContent.append(tableWidget->item(i,j)->text().mid(3));  //mid(3)从字符的第4位截取至尾部
                medicineContent.append("*");
            }
            else
            {
                medicineContent.append(tableWidget->item(i,j)->text());
            }
        }
        medicineContent.append("/");
        medicineContentStream<<medicineContent<<endl;
        medicineContent.clear();
    }

    medicineContent.append("*n");
    medicineContent.append(tableWidget->item(0,3)->text());
    medicineContentStream<<medicineContent<<endl;

    medicineFile.close();
}

int doctorScene::getMedicineIndex(QString medicineName)
{
    int index;

    if(medicineName == "附子")
    {
        index = 93201;
    }
    else if(medicineName == "干姜")
    {
        index = 93202;
    }
    else if(medicineName == "肉桂")
    {
        index = 93203;
    }
    else if(medicineName == "丁香")
    {
        index = 93204;
    }
    else if(medicineName == "茴香")
    {
        index = 93205;
    }
    else if(medicineName == "茱萸")
    {
        index = 93206;
    }
    else if(medicineName == "灵芝")
    {
        index = 93207;
    }
    else if(medicineName == "杜仲")
    {
        index = 93208;
    }
    else if(medicineName == "鱼腥草")
    {
        index = 93209;
    }
    else if(medicineName == "金银花")
    {
        index = 93210;
    }
    else if(medicineName == "甘草")
    {
        index = 93211;
    }
    else if(medicineName == "菊花")
    {
        index = 93212;
    }
    else if(medicineName == "连翘")
    {
        index = 93213;
    }
    else if(medicineName == "薄荷")
    {
        index = 93214;
    }
    else if(medicineName == "冰片")
    {
        index = 93215;
    }
    else if(medicineName == "茨实")
    {
        index = 93216;
    }
    else if(medicineName == "茯苓")
    {
        index = 93217;
    }
    else if(medicineName == "山药")
    {
        index = 93218;
    }
    else if(medicineName == "赤小豆")
    {
        index = 93219;
    }
    else if(medicineName == "薏仁")
    {
        index = 93220;
    }
    else if(medicineName == "苍术")
    {
        index = 93221;
    }
    else if(medicineName == "藿香")
    {
        index = 93222;
    }
    else if(medicineName == "麻黄")
    {
        index = 93223;
    }
    else if(medicineName == "蛇床子")
    {
        index = 93224;
    }
    else if(medicineName == "半夏")
    {
        index = 93225;
    }
    else if(medicineName == "黄柏")
    {
        index = 93226;
    }
    else if(medicineName == "川贝母")
    {
        index = 93227;
    }
    else
    {
        index = 93200;
    }
    return index;
}

void doctorScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res1/clientScene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
