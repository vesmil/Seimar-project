#include "pipeline.h"

#include <stdexcept>

#include "gstreamer/gsWrapper.h"

void Pipeline::start()
{
    if (!m_completed)
        throw std::runtime_error("Pipeline started before completion.\n");

    gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
}

void Pipeline::stop()
{
    gst_element_change_state(m_pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(m_pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

Pipeline::~Pipeline()
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
    {
        gst_object_unref(m_videoSrc);
    }
    if (m_sink)
    {
        gst_object_unref(m_sink);
    }
}

void Pipeline::setCapsFilter(const gchar* name)
{
    m_videoCaps = GsWrapper::makeDefualtCaps();

    m_capsfilter = GsWrapper::makeElement("capsfilter", name);
    g_object_set(m_capsfilter, "caps", m_videoCaps, NULL);
    gst_caps_unref(m_videoCaps);
}
