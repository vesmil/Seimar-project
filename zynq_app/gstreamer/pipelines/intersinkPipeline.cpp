#include "intersinkPipeline.h"

#include <stdexcept>
#include "gstreamer/gsWrapper.h"
#include "global/config.h"

IntersinkPipeline::IntersinkPipeline()
{
    setSource("v4l2source");
    setCapsFilter("intercaps");
    setSink("intersink");

    completePipeline();
}

IntersinkPipeline &IntersinkPipeline::getInstance()
{
    static IntersinkPipeline instance;
    return instance;
}

void IntersinkPipeline::setSource(const gchar *name)
{
    m_videoSrc = GsWrapper::makeElement("v4l2src",name);
    g_object_set(m_videoSrc,"device", glb::path::VIDEO_SRC.c_str(),"do-timestamp", TRUE, NULL);
}

void IntersinkPipeline::setSink(const gchar *name)
{
    m_sink = GsWrapper::makeElement("intervideosink",name);
    g_object_set(m_sink,"channel", GsWrapper::getDefaultIntervidChanName(), NULL);
}

void IntersinkPipeline::completePipeline()
{
    m_pipeline = gst_pipeline_new("interpipeline");

    m_bus = gst_element_get_bus(m_pipeline);
    gst_bus_add_signal_watch(m_bus);

    gst_bin_add_many(GST_BIN(m_pipeline), m_videoSrc, m_capsfilter, m_sink, NULL);

    if (!gst_element_link_many(m_videoSrc, m_capsfilter, m_sink, NULL))
        throw std::runtime_error("Elements could not be linked.\n");

    m_completed = true;
}

