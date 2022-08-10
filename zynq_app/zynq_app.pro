CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
        global/logCategories.cpp \
        library/gstreamer/gsFacade.cpp \
        library/gstreamer/gsWrapper.cpp \
        library/gstreamer/pipelines/internalPipeline.cpp \
        library/gstreamer/pipelines/pipelineBase.cpp \
    library/gstreamer/pipelines/pipelineFromInternSrc.cpp \
        library/gstreamer/pipelines/rawFilePipeline.cpp \
        library/gstreamer/pipelines/rtpPipeline.cpp \
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
        library/gstreamer/gsFacade.h \
        library/gstreamer/gsWrapper.h \
        library/gstreamer/pipelines/internalPipeline.h \
        library/gstreamer/pipelines/pipelineBase.h \
        library/gstreamer/pipelines/pipelineFromInternSrc.h \
        library/gstreamer/pipelines/rawFilePipeline.h \
        library/gstreamer/pipelines/rtpPipeline.h \
        library/visca/uartCommunication.h \
        library/visca/visca.h \
        library/visca/viscaCommands.h

