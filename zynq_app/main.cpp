#include "pipelines/rtpPipeline.h"
#include "pipelines/rawFilePipeline.h"
#include "gsWrapper.h"

#include <QCoreApplication>
#include <thread>

#include "global/config.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GsWrapper::init();

    gst_debug_set_active(TRUE);
    gst_debug_set_default_threshold(GST_LEVEL_FIXME);

    RtpPipeline rtpPipeline;
    rtpPipeline.start();

    RawFilePipeline rawFilePipeline;
    rawFilePipeline.start();

    GsWrapper::deinit();

    return a.exec();
}
