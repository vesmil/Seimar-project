QT += widgets core gui

CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
    global/logcategories.cpp \
    graphic/menu/itemlayout.cpp \
    graphic/menu/items/itembase.cpp \
    graphic/menu/items/popupitem.cpp \
    graphic/menu/items/submenuitem.cpp \
    graphic/menu/menu.cpp \
    graphic/menu/menubuilder.cpp \
    library/application/settings.cpp \
    library/gstreamer/gsfacade.cpp \
    library/gstreamer/gswrapper.cpp \
    library/gstreamer/pipelines/internalpipeline.cpp \
    library/gstreamer/pipelines/pipelinebase.cpp \
    library/gstreamer/pipelines/rawdisplaypipeline.cpp \
    library/gstreamer/pipelines/rawfilepipeline.cpp \
    library/gstreamer/pipelines/rawrtppipeline.cpp \
    library/visca/uartcommunication.cpp \
    library/visca/visca.cpp \
    main.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        global/config.h \
        global/logcategories.h \
        graphic/menu/itemlayout.h \
        graphic/menu/items/itembase.h \
        graphic/menu/items/popupitem.h \
        graphic/menu/items/submenuitem.h \
        graphic/menu/items/valueItem.h \
        graphic/menu/menu.h \
        graphic/menu/menubuilder.h \
        library/application/settings.h \
        library/gstreamer/gsfacade.h \
        library/gstreamer/gswrapper.h \
        library/gstreamer/pipelines/internalpipeline.h \
        library/gstreamer/pipelines/pipelinebase.h \
        library/gstreamer/pipelines/rawdisplaypipeline.h \
        library/gstreamer/pipelines/rawfilepipeline.h \
        library/gstreamer/pipelines/rawrtppipeline.h \
        library/visca/uartcommunication.h \
        library/visca/visca.h \
        library/visca/viscaCommands.h

FORMS +=

