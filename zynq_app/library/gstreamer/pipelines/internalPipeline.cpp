#include "internalPipeline.h"

#include "library/gstreamer/gsWrapper.h"
#include "global/logCategories.h"
#include "global/config.h"

const gchar* InternalPipeline::m_intervideoChannelName  = "interchannel";

InternalPipeline::InternalPipeline() : PipelineBase()
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
    m_data.videoSrc = GsWrapper::makeElement("v4l2src",name);
    g_object_set(m_data.videoSrc,"device", glb::path::VIDEO_SRC.c_str(),"do-timestamp", TRUE, nullptr);
}

void InternalPipeline::setSink(const gchar *name)
{
    m_data.sink = GsWrapper::makeElement("intervideosink",name);
    g_object_set(m_data.sink, "channel", m_intervideoChannelName, nullptr);
}

void InternalPipeline::completePipeline()
{
    m_data.pipeline = gst_pipeline_new("interpipeline");

    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    gst_bin_add_many(GST_BIN(m_data.pipeline), m_data.videoSrc, m_data.capsFilter, m_data.sink, nullptr);

    bool result = gst_element_link_many(m_data.videoSrc, m_data.capsFilter, m_data.sink, nullptr);
    checkResult(result);
}

const gchar* InternalPipeline::getChannelName()
{
    return m_intervideoChannelName;
}
