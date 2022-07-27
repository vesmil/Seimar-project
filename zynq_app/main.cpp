#include "pipelines/rtpPipeline.h"
#include "pipelines/rawFilePipeline.h"
#include "gsWrapper.h"

#include <QCoreApplication>
#include <thread>

#include "global/config.h"

void intersrc() {
    GstBus *bus;
    GstElement *videosrc, *capsfilter, *sink, *pipeline;
    GstCaps *videoCaps;

    videosrc = GsWrapper::makeElement("intervideosrc", "intersrc");
    g_object_set(videosrc,"channel", GsWrapper::getIntervideoChannel(), NULL);

    // Sink
    sink = GsWrapper::makeElement("udpsink", "udpsink");
    g_object_set(sink, "port", glb::rtp::PORT, NULL);
    g_object_set(sink, "host", glb::rtp::IP_ADDRESS.c_str(), NULL);

    // Caps
    videoCaps = gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB",
            "framerate", GST_TYPE_FRACTION, 60, 1,
            "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
            "width", G_TYPE_INT, glb::dim::WIDTH,
            "height", G_TYPE_INT, glb::dim::HEIGHT,
            NULL);

    capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    g_object_set(capsfilter, "caps", videoCaps, NULL);

    gst_caps_unref(videoCaps);

    GstElement *rtpvrawpay = GsWrapper::makeElement("rtpvrawpay", "rtpvrawpay");

    pipeline = gst_pipeline_new("pipeline");

    bus = gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, rtpvrawpay, sink, NULL);
    gst_element_link_many(videosrc, capsfilter, rtpvrawpay, sink, NULL);

    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void intersink() {
    GstBus *bus;
    GstElement *videosrc, *capsfilter, *sink, *pipeline;
    GstCaps *videoCaps;

    videosrc = gst_element_factory_make("v4l2src", "videosrc");
    g_object_set(videosrc,"device", glb::path::VIDEO_SRC.c_str(),
                 "do-timestamp", TRUE, NULL);

    // Sink
    sink = GsWrapper::makeElement("intervideosink","intersink");
    g_object_set(sink,"channel", GsWrapper::getIntervideoChannel(), NULL);

    // Caps
    videoCaps = gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB",
            "framerate", GST_TYPE_FRACTION, 60, 1,
            "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
            "width", G_TYPE_INT, glb::dim::WIDTH,
            "height", G_TYPE_INT, glb::dim::HEIGHT,
            NULL);

    capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    g_object_set(capsfilter, "caps", videoCaps, NULL);

    gst_caps_unref(videoCaps);

    pipeline = gst_pipeline_new("pipeline");

    bus = gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, sink, NULL);
    gst_element_link_many(videosrc, capsfilter, sink, NULL);

    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    GsWrapper::init();

    gst_debug_set_active(TRUE);
    gst_debug_set_default_threshold(GST_LEVEL_FIXME);

    RtpPipeline rtpPipeline;
    rtpPipeline.start();

    RawFilePipeline rawFilePipeline;
    rawFilePipeline.start();

    GsWrapper::deinit();
    */

    if (!gst_is_initialized()) {
        gst_init(nullptr, nullptr);
    }

    gst_debug_set_active(TRUE);
    gst_debug_set_default_threshold(GST_LEVEL_FIXME);

    intersrc();
    intersink();

    return a.exec();
}
