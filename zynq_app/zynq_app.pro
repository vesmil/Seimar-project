CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
        main.cpp \
        gsWrapper.cpp \
        pipelines/pipelineBase.cpp \
        pipelines/rawFilePipeline.cpp \
    pipelines/rtpPipeline.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ethernetPipeline.h \
    global/constans.h \
    gsWrapper.h \
    pipelines/pipelineBase.h \
    pipelines/rawFilePipeline.h \
    pipelines/rtpPipeline.h \
    rawFilePipeline.h
