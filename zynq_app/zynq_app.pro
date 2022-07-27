CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
    gstreamer/gsFacade.cpp \
    gstreamer/gsWrapper.cpp \
    gstreamer/pipelines/abstract/intersrcPipeline.cpp \
    gstreamer/pipelines/abstract/pipeline.cpp \
    gstreamer/pipelines/intersinkPipeline.cpp \
    gstreamer/pipelines/rawFilePipeline.cpp \
    gstreamer/pipelines/rtpPipeline.cpp \
        main.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        global/config.h \
    gstreamer/gsFacade.h \
    gstreamer/gsWrapper.h \
    gstreamer/pipelines/abstract/intersrcPipeline.h \
    gstreamer/pipelines/abstract/pipeline.h \
    gstreamer/pipelines/intersinkPipeline.h \
    gstreamer/pipelines/rawFilePipeline.h \
    gstreamer/pipelines/rtpPipeline.h

