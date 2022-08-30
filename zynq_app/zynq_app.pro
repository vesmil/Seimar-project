QT += widgets core gui

CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
    global/logcategories.cpp \
    graphic/mainWindow.cpp \
    graphic/menu/items/itembase.cpp \
    graphic/menu/items/popupitem.cpp \
    graphic/menu/items/submenuitem.cpp \
    graphic/menu/menu.cpp \
    graphic/menu/menubuilder.cpp \
    graphic/qtpalettes.cpp \
    library/application/settings.cpp \
    library/visible/gstreamer/gsfacade.cpp \
    library/visible/gstreamer/pipelines/internalpipeline.cpp \
    library/visible/gstreamer/pipelines/pipelinebase.cpp \
    library/visible/gstreamer/pipelines/rawdisplaypipeline.cpp \
    library/visible/gstreamer/pipelines/rawfilepipeline.cpp \
    library/visible/gstreamer/pipelines/rawrtppipeline.cpp \
    library/visible/visca/uartcommunication.cpp \
    library/visible/visca/visca.cpp \
    main.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        global/config.h \
        global/logcategories.h \
        graphic/mainWindow.h \
        graphic/menu/items/itembase.h \
        graphic/menu/items/popupitem.h \
        graphic/menu/items/submenuitem.h \
        graphic/menu/items/valueItem.h \
        graphic/menu/menu.h \
        graphic/menu/menubuilder.h \
        graphic/qtpalettes.h \
        library/application/settings.h \
        library/visible/gstreamer/gsfacade.h \
        library/visible/gstreamer/pipelines/internalpipeline.h \
        library/visible/gstreamer/pipelines/pipelinebase.h \
        library/visible/gstreamer/pipelines/rawdisplaypipeline.h \
        library/visible/gstreamer/pipelines/rawfilepipeline.h \
        library/visible/gstreamer/pipelines/rawrtppipeline.h \
        library/visible/visca/uartcommunication.h \
        library/visible/visca/visca.h \
        library/visible/visca/viscaCommands.h

FORMS +=

