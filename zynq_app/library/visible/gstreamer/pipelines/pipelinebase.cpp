#include "pipelinebase.h"

#include "global/logcategories.h"
#include "library/visible/gstreamer/gsfacade.h"
#include "library/visible/gstreamer/pipelines/internalpipeline.h"

void Pipelinebase::start() const
{
    if (!m_completed)
    {
        qCWarning(gsLog()) << "Couldn't start pipeline because it was not completed.";
        return;
    }

    gst_element_set_state (m_data.pipeline, GST_STATE_PLAYING);
}

void Pipelinebase::stop() const
{
    gst_element_change_state(m_data.pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(m_data.pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

Pipelinebase::~Pipelinebase()
{
    if (m_data.bus)
    {
        gst_bus_remove_signal_watch(m_data.bus);
        gst_object_unref(m_data.bus);
    }

    if (m_data.pipeline)
    {
        gst_element_set_state(m_data.pipeline, GST_STATE_NULL);
        gst_object_unref(m_data.pipeline);
    }

    if (m_data.videoSrc)
    {
        gst_object_unref(m_data.videoSrc);
    }

    if (m_data.queue)
    {
        gst_object_unref(m_data.queue);
    }
    if (m_data.capsFilter)
    {
        gst_object_unref(m_data.capsFilter);
    }

    if (m_data.sink)
    {
        gst_object_unref(m_data.sink);
    }
}

bool Pipelinebase::isCompleted()
{
    return m_completed;
}

void Pipelinebase::setDefaultCapsFilter(const gchar* name)
{
    m_data.videoCaps = gst_caps_new_simple("video/x-raw",
                                      "framerate", GST_TYPE_FRACTION, 30, 1,
                                      "format", G_TYPE_STRING, "RGB",
                                      "width", G_TYPE_INT, WIDTH,
                                      "height", G_TYPE_INT, HEIGHT, NULL);

    m_data.capsFilter = GsFacade::makeElement("capsfilter", name);
    g_object_set(m_data.capsFilter, "caps", m_data.videoCaps, NULL);
    gst_caps_unref(m_data.videoCaps);
}

void Pipelinebase::setQueue(const gchar* name)
{
    m_data.queue = GsFacade::makeElement("queue", name);
}

void Pipelinebase::setSrcFromInternalPipeline(const gchar *name)
{
    m_data.videoSrc = GsFacade::makeElement("intervideosrc", name);
    g_object_set(m_data.videoSrc, "channel", InternalPipeline::getChannelName(), nullptr);
}

void Pipelinebase::completePipeline(const gchar *name)
{
    m_data.pipeline = gst_pipeline_new(name);

    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    m_completed = addAndLink(m_data.pipeline, m_data.videoSrc, m_data.capsFilter, m_data.sink);
}
