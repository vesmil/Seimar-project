CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0

SOURCES += \
        main.cpp \
        gsWrapper.cpp \
        pipelines/abstract/intersrcPipeline.cpp \
        pipelines/abstract/pipeline.cpp \
        pipelines/intersinkPipeline.cpp \
        pipelines/rawFilePipeline.cpp \
        pipelines/rtpPipeline.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        global/config.h \
        gsWrapper.h \
        rtpPipeline.h \
        pipelines/abstract/intersrcPipeline.h \
        pipelines/abstract/pipeline.h \
        pipelines/intersinkPipeline.h \
        pipelines/rawFilePipeline.h \
        pipelines/rtpPipeline.h \
