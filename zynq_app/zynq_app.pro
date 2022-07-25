CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
        main.cpp \
        pipelines/ethernetPipeline.cpp \
        pipelines/pipelineBase.cpp \
        pipelines/rawFilePipeline.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ethernetPipeline.h \
    global/constans.h \
    pipelines/ethernetPipeline.h \
    pipelines/pipelineBase.h \
    pipelines/rawFilePipeline.h \
    rawFilePipeline.h
