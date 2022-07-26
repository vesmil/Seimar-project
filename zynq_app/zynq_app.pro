CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
        main.cpp \
        gsWrapper.cpp \
    pipelines/intersinkPipeline.cpp \
    pipelines/intersrcPipeline.cpp \
    pipelines/pipeline.cpp \
        pipelines/rawFilePipeline.cpp \
    pipelines/rtpPipeline.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ethernetPipeline.h \
    global/config.h \
    gsWrapper.h \
    pipelines/intersinkPipeline.h \
    pipelines/intersrcPipeline.h \
    pipelines/pipeline.h \
    pipelines/rawFilePipeline.h \
    pipelines/rtpPipeline.h \
    rawFilePipeline.h
