CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
        global/logCategories.cpp \
        library/gstreamer/gsFacade.cpp \
        library/gstreamer/gsWrapper.cpp \
        library/gstreamer/pipelines/abstract/intersrcPipeline.cpp \
        library/gstreamer/pipelines/abstract/pipeline.cpp \
        library/gstreamer/pipelines/intersinkPipeline.cpp \
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
        library/gstreamer/pipelines/abstract/intersrcPipeline.h \
        library/gstreamer/pipelines/abstract/pipeline.h \
        library/gstreamer/pipelines/intersinkPipeline.h \
        library/gstreamer/pipelines/rawFilePipeline.h \
        library/gstreamer/pipelines/rtpPipeline.h \
        library/visca/uartCommunication.h \
        library/visca/visca.h \
        library/visca/viscaCommands.h

