QT += widgets core gui

CONFIG += c++1z link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

# DEFINES += QT_NO_INFO_OUTPUT

SOURCES += \
    global/logcategories.cpp \
    global/utility.cpp \
    graphic/mainwindow.cpp \
    graphic/menu/items/itembase.cpp \
    graphic/menu/items/popupitem.cpp \
    graphic/menu/items/submenuitem.cpp \
    graphic/menu/items/valueitem.cpp \
    graphic/menu/menu.cpp \
    graphic/menu/menubuilder.cpp \
    graphic/style.cpp \
    library/application/settings.cpp \
    library/controller/controller.cpp \
    library/controller/elements/iterable.cpp \
    library/visible/gstreamer/gsfacade.cpp \
    library/visible/gstreamer/pipelines/internalpipeline.cpp \
    library/visible/gstreamer/pipelines/pipelinebase.cpp \
    library/visible/gstreamer/pipelines/rawdisplaypipeline.cpp \
    library/visible/gstreamer/pipelines/rawfilepipeline.cpp \
    library/visible/gstreamer/pipelines/rawrtppipeline.cpp \
    library/visible/visca/uartcommunication.cpp \
    library/visible/visca/visca.cpp \
    main.cpp

HEADERS += \
    global/logcategories.h \
    global/utility.h \
    graphic/mainwindow.h \
    graphic/menu/items/itembase.h \
    graphic/menu/items/popupitem.h \
    graphic/menu/items/submenuitem.h \
    graphic/menu/items/valueitem.h \
    graphic/menu/menu.h \
    graphic/menu/menubuilder.h \
    graphic/style.h \
    library/application/settings.h \
    library/controller/controller.h \
    library/controller/elements/controllercommand.h \
    library/controller/elements/iterable.h \
    library/controller/elements/popup.h \
    library/controller/elements/setter.h \
    library/controller/elements/textsetter.h \
    library/visible/gstreamer/gsfacade.h \
    library/visible/gstreamer/pipelines/internalpipeline.h \
    library/visible/gstreamer/pipelines/pipelinebase.h \
    library/visible/gstreamer/pipelines/rawdisplaypipeline.h \
    library/visible/gstreamer/pipelines/rawfilepipeline.h \
    library/visible/gstreamer/pipelines/rawrtppipeline.h \
    library/visible/visca/uartcommunication.h \
    library/visible/visca/visca.h \
    library/visible/visca/viscaCommands.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

