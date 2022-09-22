#include "rawrtppipeline.h"

#include "library/application/settings.h"
#include "library/visible/gstreamer/gsfacade.h"

RawRtpPipeline::RawRtpPipeline() : PipelineBase()
{
    setSrcFromInternalPipeline("rtp-source");
    setQueue("rtp-queue");
    setDefaultCapsFilter("rtp-caps");
    setRtpPayload();
    setUdpsink();
    completePipeline();
}

void RawRtpPipeline::setRtpPayload()
{
    m_rtp_data.rtpvrawpay = GsFacade::makeElement("rtpvrawpay", "rtp-pay");
    g_object_set(m_data.sink, "mtu", 60000, nullptr);
}

void RawRtpPipeline::setUdpsink()
{
    m_data.sink = GsFacade::makeElement("udpsink", "rtp-sink");

    g_object_set(m_data.sink, "port", Settings::getInstance().rtp.port, "host", Settings::getInstance().rtp.ip_address.c_str(),
                 "sync", false, "async", false, nullptr);
}

void RawRtpPipeline::completePipeline()
{
    m_data.pipeline = gst_pipeline_new("rtp-pipeline");
    m_data.bus = gst_element_get_bus(m_data.pipeline);
    gst_bus_add_signal_watch(m_data.bus);

    m_completed = addAndLink(m_data.pipeline, m_data.videoSrc, m_data.queue, m_data.capsFilter, m_rtp_data.rtpvrawpay, m_data.sink);
}

RawRtpPipeline::~RawRtpPipeline()
{
    stop();

    if (m_rtp_data.rtpvrawpay)
        gst_object_unref(m_rtp_data.rtpvrawpay);
}
