#include "pipelineBase.h"

#include <gsWrapper.h>
#include <stdexcept>

PipelineBase::PipelineBase()
{
}

void PipelineBase::start()
{
    if (m_completed)
        gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
    else
        throw std::runtime_error("Pipeline start before completion.\n");
}

void PipelineBase::stop()
{
    gst_element_change_state(m_pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(m_pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

PipelineBase::~PipelineBase()
{
    unrefAll();
}

void PipelineBase::unrefAll()
{
    if (m_bus)
    {
        gst_bus_remove_signal_watch(m_bus);
        gst_object_unref(m_bus);
    }

    if (m_pipeline)
    {
        gst_element_set_state(m_pipeline, GST_STATE_NULL);
        gst_object_unref(m_pipeline);
    }

    if (m_videoSrc)
        gst_object_unref(m_videoSrc);

    if (m_sink)
        gst_object_unref(m_sink);
}

void PipelineBase::setSource(const gchar* name)
{
    m_videoSrc = GSWrapper::makeElement("v4l2src",name);
    g_object_set(m_videoSrc,"device", glb::path::VIDEO_SRC.c_str(), NULL); // "do-timestamp", TRUE
}

void PipelineBase::setCapsFilter(const gchar* name)
{
    m_videoCaps = gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB",
            "framerate", GST_TYPE_FRACTION, 60, 1,
            "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
            "width", G_TYPE_INT, glb::dim::WIDTH,
            "height", G_TYPE_INT, glb::dim::HEIGHT,
            NULL);

    m_capsfilter = GSWrapper::makeElement("capsfilter", name);
    g_object_set(m_capsfilter, "caps", m_videoCaps, NULL);
    gst_caps_unref(m_videoCaps);
}
