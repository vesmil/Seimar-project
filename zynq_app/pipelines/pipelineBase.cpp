#include "pipelineBase.h"

#include <stdexcept>

PipelineBase::PipelineBase()
{
    if (!gst_is_initialized())
    {
        gst_init(nullptr, nullptr);
    }

    set_source();
    set_caps_filter();
}

void PipelineBase::start()
{
    if (completed)
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
    else
        throw std::runtime_error("Pipeline start before completion.\n");
}

void PipelineBase::stop()
{
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

PipelineBase::~PipelineBase()
{
    unref_all();
}

void PipelineBase::unref_all()
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
        gst_object_unref(videosrc);

    if (sink)
        gst_object_unref(sink);
}

void PipelineBase::set_source()
{
    videosrc = gst_element_factory_make("v4l2src", "videosrc");
    g_object_set(videosrc,"device", glb::path::VIDEO_SRC.c_str(),
                 "io-mode", 4, "do-timestamp", TRUE, NULL);
}

void PipelineBase::set_caps_filter()
{
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
}
