#include "internalPipeline.h"

#include "library/gstreamer/gsWrapper.h"
#include "global/logCategories.h"
#include "global/config.h"

InternalPipeline::InternalPipeline() : PipelineBase()
{
    setSource("v4l2source");
    setCapsFilter("intercaps");
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
    m_videoSrc = GsWrapper::makeElement("v4l2src",name);
    g_object_set(m_videoSrc,"device", glb::path::VIDEO_SRC.c_str(),"do-timestamp", TRUE, nullptr);
}

void InternalPipeline::setSink(const gchar *name)
{
    m_sink = GsWrapper::makeElement("intervideosink",name);
    g_object_set(m_sink,"channel", GsWrapper::getDefaultIntervidChanName(), nullptr);
}

void InternalPipeline::completePipeline()
{
    m_pipeline = gst_pipeline_new("interpipeline");

    m_bus = gst_element_get_bus(m_pipeline);
    gst_bus_add_signal_watch(m_bus);

    gst_bin_add_many(GST_BIN(m_pipeline), m_videoSrc, m_capsfilter, m_sink, nullptr);

    if (!gst_element_link_many(m_videoSrc, m_capsfilter, m_sink, nullptr))
        qCWarning(gsLog()) << "Elements could not be linked.\n";
    else
        m_completed = true;
}

