QT += widgets core gui

CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
    global/logCategories.cpp \
    graphic/menu/itemlayout.cpp \
    graphic/menu/items/itemBase.cpp \
    graphic/menu/items/popupItem.cpp \
    graphic/menu/items/submenuitem.cpp \
    graphic/menu/menu.cpp \
    graphic/menu/menuBuilder.cpp \
    library/application/settings.cpp \
    library/gstreamer/gsFacade.cpp \
    library/gstreamer/gsWrapper.cpp \
    library/gstreamer/pipelines/internalPipeline.cpp \
    library/gstreamer/pipelines/pipelineBase.cpp \
    library/gstreamer/pipelines/rawDisplayPipeline.cpp \
    library/gstreamer/pipelines/rawFilePipeline.cpp \
    library/gstreamer/pipelines/rawRtpPipeline.cpp \
    library/visca/uartCommunication.cpp \
    library/visca/visca.cpp \
    main.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        global/config.h \
        global/logCategories.h \
        graphic/menu/itemlayout.h \
        graphic/menu/items/itemBase.h \
        graphic/menu/items/popupItem.h \
        graphic/menu/items/submenuitem.h \
        graphic/menu/items/valueItem.h \
        graphic/menu/menu.h \
        graphic/menu/menuBuilder.h \
        library/application/settings.h \
        library/gstreamer/gsFacade.h \
        library/gstreamer/gsWrapper.h \
        library/gstreamer/pipelines/internalPipeline.h \
        library/gstreamer/pipelines/pipelineBase.h \
        library/gstreamer/pipelines/rawDisplayPipeline.h \
        library/gstreamer/pipelines/rawFilePipeline.h \
        library/gstreamer/pipelines/rawRtpPipeline.h \
        library/visca/uartCommunication.h \
        library/visca/visca.h \
        library/visca/viscaCommands.h

FORMS +=

