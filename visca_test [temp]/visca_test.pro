QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../zynq_app/library/visible/visca/uartcommunication.cpp \
    ../zynq_app/library/visible/visca/visca.cpp \
    global/logcategories.cpp \
    lib/gstreamer/visible.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../zynq_app/library/visible/visca/uartcommunication.h \
    ../zynq_app/library/visible/visca/visca.h \
    ../zynq_app/library/visible/visca/viscacommands.h \
    global/logcategories.h \
    lib/gstreamer/visible.h \
    mainwindow.h

LIBS +=  -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstrtspserver-1.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
