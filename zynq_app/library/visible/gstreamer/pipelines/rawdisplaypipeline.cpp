#include "rawdisplaypipeline.h"

#include "library/visible/gstreamer/gsfacade.h"

RawDisplayPipeline::RawDisplayPipeline()
{
    setSrcFromInternalPipeline("display-source");
    setQueue("display-queue");
    setVideoconvert();
    setVideoscale();
    setDefaultCapsFilter("display-caps");
    setKmssink();
    completePipeline("display-pipeline");
}

void RawDisplayPipeline::setKmssink()
{
    m_data.sink = GsFacade::makeElement("kmssink", "kmssink");
    g_object_set(m_data.sink, "bus-id", "a0000000.v_mix", "plane-id", 36 ,"fullscreen-overlay", false, "sync", false, NULL);
}

RawDisplayPipeline::~RawDisplayPipeline()
{
    stop();
}

void RawDisplayPipeline::setVideoconvert()
{
    m_displayData.videoconvert = GsFacade::makeElement("videoconvert", "videoconvert");
}

void RawDisplayPipeline::setVideoscale()
{
    m_displayData.videoscale = GsFacade::makeElement("videoscale", "videoscale");
}

void RawDisplayPipeline::completePipeline(const gchar *name)
{
    m_data.pipeline = gst_pipeline_new(name);

    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    m_completed = addAndLink(m_data.pipeline, m_data.videoSrc, m_data.queue, m_displayData.videoscale, m_displayData.videoconvert ,m_data.capsFilter, m_data.sink);
}
