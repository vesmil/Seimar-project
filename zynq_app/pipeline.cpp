#include "pipeline.h"

#include <stdexcept>
#include <thread>

Pipeline::Pipeline()
{
    if (TRUE){
        g_print("tr");
    }

    if (!FALSE){
        g_print("fs");
    }

    if (!gst_is_initialized())
    {
        gst_init(nullptr, nullptr);
    }

    videosrc = gst_element_factory_make("v4l2src", "videosrc");
    g_object_set(videosrc,"device", glb::constants::VIDEO_SRC_PATH.c_str(),
                 "io-mode", 4,
                 "do-timestamp", TRUE, NULL);

    sink = gst_element_factory_make("filesink", "sink");
    g_object_set(sink, "location", glb::constants::OUT_PATH.c_str(), NULL);

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

    pipeline = gst_pipeline_new("pipeline");
    bus = gst_element_get_bus(pipeline);

    // GstElement *timeoverlay = gst_element_factory_make("timeoverlay", "timeoverlay");

    gst_bin_add_many(GST_BIN(pipeline), videosrc, /* timeoverlay ,*/ capsfilter, sink, NULL);

    if (!gst_element_link_many(videosrc, /* timeoverlay, */ capsfilter, sink, NULL))
    {
        throw std::runtime_error("Elements could not be linked.\n");
    }

    start_video();
}

void Pipeline::start_video()
{
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void Pipeline::stop_video()
{
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}


Pipeline::~Pipeline()
{
    stop_video();
    unref_all();
    gst_deinit();
}

void Pipeline::unref_all()
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

    if (sink)
    {
        gst_object_unref(sink);
    }
}
