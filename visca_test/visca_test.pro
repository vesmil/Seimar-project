QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global/logCategories.cpp \
    library/gstreamer/visible.cpp \
    library/visca/uartCommunication.cpp \
    library/visca/visca.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    global/logCategories.h \
    library/gstreamer/visible.h \
    library/visca/uartCommunication.h \
    library/visca/visca.h \
    mainwindow.h

LIBS +=  -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstrtspserver-1.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
