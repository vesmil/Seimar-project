#include "rawFilePipeline.h"

#include "gsWrapper.h"
#include <stdexcept>

RawFilePipeline::RawFilePipeline() : IntersrcPipeline()
{
    setSource("rawsource");
    setCapsFilter("rawcaps");
    setFilesink();
    completePipeline();
}

void RawFilePipeline::setFilesink()
{
    m_sink = GstWrapper::makeElement("filesink", "filesink");
    g_object_set(m_sink, "location", glb::path::VIDEO_OUT.c_str(), NULL);
}

void RawFilePipeline::completePipeline()
{
    m_pipeline = gst_pipeline_new("rawpipeline");

    m_bus = gst_element_get_bus(m_pipeline);
    gst_bus_add_signal_watch(m_bus);

    gst_bin_add_many(GST_BIN(m_pipeline), m_videoSrc, m_capsfilter, m_sink, NULL);

    if (!gst_element_link_many(m_videoSrc, m_capsfilter, m_sink, NULL))
        throw std::runtime_error("Elements could not be linked.\n");

    m_completed = true;
}

RawFilePipeline::~RawFilePipeline()
{
    stop();
}
