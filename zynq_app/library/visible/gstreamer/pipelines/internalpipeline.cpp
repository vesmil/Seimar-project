#include "internalpipeline.h"

#include "library/visible/gstreamer/gsfacade.h"
#include "library/application/settings.h"

const gchar* InternalPipeline::m_intervideoChannelName  = "interchannel";

InternalPipeline::InternalPipeline() : Pipelinebase()
{
    setSource("v4l2source");
    setDefaultCapsFilter("intercaps");
    setSink("intersink");
    completePipeline();
}

InternalPipeline &InternalPipeline::getInstance()
{
    static InternalPipeline instance;
    return instance;
}

void InternalPipeline::setSource(const gchar *name)
{
    m_data.videoSrc = GsFacade::makeElement("v4l2src",name);
    g_object_set(m_data.videoSrc,"device", Settings::getInstance().path.videoSrc.c_str(), nullptr); // "do-timestamp", TRUE,
}

void InternalPipeline::setSink(const gchar *name)
{
    m_data.sink = GsFacade::makeElement("intervideosink",name);
    g_object_set(m_data.sink, "channel", m_intervideoChannelName, nullptr);
}

void InternalPipeline::completePipeline()
{
    m_data.pipeline = gst_pipeline_new("interpipeline");
    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    m_completed = addAndLink(m_data.pipeline, m_data.videoSrc, m_data.capsFilter, m_data.sink);
}

const gchar* InternalPipeline::getChannelName()
{
    return m_intervideoChannelName;
}
