#include "ethernetPipeline.h"

#include <stdexcept>
#include <thread>

EthernetPipeline::EthernetPipeline()
{
    if (!gst_is_initialized())
    {
        gst_init(nullptr, nullptr);
    }

    set_source();
    set_caps_filter();
    set_rtp_payload();
    set_udpsink();
    set_pipeline();
}

void EthernetPipeline::set_source()
{
    videosrc = gst_element_factory_make("v4l2src", "videosrc");
    g_object_set(videosrc,"device", glb::constants::VIDEO_SRC_PATH.c_str(),
                 "io-mode", 4, "do-timestamp", TRUE, NULL);
}

void EthernetPipeline::set_caps_filter()
{
    videoCaps = gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB",
            "framerate", GST_TYPE_FRACTION, 60, 1,
            "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
            "width", G_TYPE_INT, glb::constants::WIDTH,
            "height", G_TYPE_INT, glb::constants::HEIGHT,
            NULL);

    capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    g_object_set(capsfilter, "caps", videoCaps, NULL);
    gst_caps_unref(videoCaps);
}

void EthernetPipeline::set_rtp_payload()
{
    rtpvrawpay = gst_element_factory_make("rtpvrawpay", "rtpvrawpay");
}

void EthernetPipeline::set_udpsink()
{
    udpsink = gst_element_factory_make("udpsink", "sink");

    // TODO temp
    g_object_set(udpsink, "port", 9002, NULL);
    g_object_set(udpsink, "host", "10.15.1.77", NULL);
}

void EthernetPipeline::set_pipeline()
{
    pipeline = gst_pipeline_new("pipeline");
    bus = gst_element_get_bus(pipeline);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, rtpvrawpay, udpsink, NULL);

    if (!gst_element_link_many(videosrc, capsfilter, rtpvrawpay, udpsink, NULL))
    {
        throw std::runtime_error("Elements could not be linked.\n");
    }
}

void EthernetPipeline::start_broadcast()
{
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void EthernetPipeline::stop_broadcast()
{
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

EthernetPipeline::~EthernetPipeline()
{
    stop_broadcast();
    unref_all();
    gst_deinit();
}

void EthernetPipeline::unref_all()
{
    if (bus)
    {
        gst_bus_remove_signal_watch(bus);
        gst_object_unref(bus);
    }
    if (pipeline)
    {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }
    if (videosrc)
    {
        gst_object_unref(videosrc);
    }
    if (udpsink)
    {
        gst_object_unref(udpsink);
    }

    gst_object_unref(rtpvrawpay);
}
