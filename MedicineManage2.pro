QT       += core gui
QT       += axcontainer
QT       += xml
QT       += serialport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientbackbutton.cpp \
    clientscene.cpp \
    loadbutton.cpp \
    main.cpp \
    mypushbutton.cpp \
    opencvscene.cpp \
    registerbutton.cpp \
    registerscene.cpp \
    widget.cpp \
    doctorscene.cpp \
    doctorbactbutton.cpp \
    storehousescene.cpp \
    analysis.cpp

HEADERS += \
    clientbackbutton.h \
    clientscene.h \
    loadbutton.h \
    mypushbutton.h \
    registerbutton.h \
    registerscene.h \
    widget.h \
    doctorscene.h \
    doctorbactbutton.h \
    opencvscene.h \
    storehousescene.h \
    analysis.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH +=   E:\DiySec\opencv\build\include
                 E:\DiySec\opencv\build\include\opencv
                 E:\DiySec\opencv\build\include\opencv2


LIBS += E:\DiySec\buildOpencv\lib\libopencv_*.a


RESOURCES += \
    res.qrc


