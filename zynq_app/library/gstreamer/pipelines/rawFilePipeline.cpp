#include "rawFilePipeline.h"

#include "global/config.h"
#include "global/logCategories.h"
#include "library/gstreamer/gsWrapper.h"

RawFilePipeline::RawFilePipeline() : PipelineBase()
{
    setSrcFromInternalPipeline("rawsource");
    setDefaultCapsFilter("rawcaps");
    setFilesink();
    completePipeline();
}

void RawFilePipeline::setFilesink()
{
    m_data.sink = GsWrapper::makeElement("filesink", "filesink");
    g_object_set(m_data.sink, "location", glb::path::VIDEO_OUT.c_str(), nullptr);
}

void RawFilePipeline::completePipeline()
{
    m_data.pipeline = gst_pipeline_new("rawpipeline");

    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    gst_bin_add_many(GST_BIN(m_data.pipeline), m_data.videoSrc, m_data.capsFilter, m_data.sink, nullptr);

    if (!gst_element_link_many(m_data.videoSrc, m_data.capsFilter, m_data.sink, nullptr))
        qCWarning(gsLog()) << "Elements could not be linked.\n";
    else
        m_completed = true;
}

RawFilePipeline::~RawFilePipeline()
{
    stop();
}
