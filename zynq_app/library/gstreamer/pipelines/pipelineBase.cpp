#include "pipelineBase.h"

#include "../gsWrapper.h"
#include "global/logCategories.h"

void PipelineBase::start() const
{
    if (!m_completed)
    {
        qCWarning(gsLog()) << "Couldn't start pipeline because it was not completed.";
        return;
    }

    gst_element_set_state (m_data.pipeline, GST_STATE_PLAYING);
}

void PipelineBase::stop() const
{
    gst_element_change_state(m_data.pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(m_data.pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

PipelineBase::~PipelineBase()
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
        gst_object_unref(m_data.videoSrc);

    if (m_data.sink)
        gst_object_unref(m_data.sink);
}

void PipelineBase::setDefaultCapsFilter(const gchar* name)
{
    /* TODO put back
    m_data.videoCaps = gst_caps_new_simple("video/x-raw",
                                      "format", G_TYPE_STRING, "RGB",
                                      "framerate", GST_TYPE_FRACTION, 60, 1,
                                      "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
                                      "width", G_TYPE_INT, WIDTH,
                                      "height", G_TYPE_INT, HEIGHT, NULL);
    */

    m_data.videoCaps = gst_caps_new_any();

    m_data.capsFilter = GsWrapper::makeElement("capsfilter", name);
    g_object_set(m_data.capsFilter, "caps", m_data.videoCaps, NULL);
    gst_caps_unref(m_data.videoCaps);
}

void PipelineBase::setSrcFromInternalPipeline(const gchar *name)
{
    m_data.videoSrc = GsWrapper::makeElement("intervideosrc", name);
    g_object_set(m_data.videoSrc, "channel", InternalPipeline::getChannelName(), nullptr);
}

void PipelineBase::checkResult(bool linkingResult)
{
    if (!linkingResult)
        qCWarning(gsLog()) << "Elements could not be linked.";
    else
        m_completed = true;
}

void PipelineBase::completePipeline(const gchar *name)
{
    m_data.pipeline = gst_pipeline_new(name);

    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    gst_bin_add_many(GST_BIN(m_data.pipeline), m_data.videoSrc, m_data.capsFilter, m_data.sink, nullptr);

    bool result = gst_element_link_many(m_data.videoSrc, m_data.capsFilter, m_data.sink, nullptr);
    checkResult(result);
}
