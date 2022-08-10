#include "pipelineBase.h"

#include "library/gstreamer/gsWrapper.h"
#include "global/logCategories.h"

void PipelineBase::start()
{
    if (!m_completed)
    {
        qCWarning(gsLog()) << "Couldn't start pipeline because it was not completed.";
        return;
    }

    gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
}

void PipelineBase::stop()
{
    gst_element_change_state(m_pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(m_pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

PipelineBase::~PipelineBase()
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

void PipelineBase::setCapsFilter(const gchar* name)
{
    // TODO move away
    m_videoCaps = gst_caps_new_simple("video/x-raw",
                                      "format", G_TYPE_STRING, "RGB",
                                      "framerate", GST_TYPE_FRACTION, 60, 1,
                                      "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
                                      "width", G_TYPE_INT, 1024,
                                      "height", G_TYPE_INT, 768, NULL);

    m_capsfilter = GsWrapper::makeElement("capsfilter", name);
    g_object_set(m_capsfilter, "caps", m_videoCaps, NULL);
    gst_caps_unref(m_videoCaps);
}
