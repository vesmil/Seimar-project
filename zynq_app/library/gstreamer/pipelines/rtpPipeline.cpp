#include "rtpPipeline.h"

#include <stdexcept>
#include <thread>
#include "global/config.h"
#include "library/gstreamer/gsWrapper.h"

RtpPipeline::RtpPipeline()
{
    setSource("rtpsource");
    setCapsFilter("rtpcaps");
    setRtpPayload();
    setUdpsink();
    completePipeline();
}

void RtpPipeline::setRtpPayload()
{
    m_rtpvrawpay = GsWrapper::makeElement("rtpvrawpay", "rtpvrawpay");
}

void RtpPipeline::setUdpsink()
{
    m_sink = GsWrapper::makeElement("udpsink", "udpsink");

    g_object_set(m_sink, "port", glb::rtp::PORT, NULL);
    g_object_set(m_sink, "host", glb::rtp::IP_ADDRESS.c_str(), NULL);
}

void RtpPipeline::completePipeline()
{
    m_pipeline = gst_pipeline_new("rtppipeline");
    m_bus = gst_element_get_bus(m_pipeline);
    gst_bus_add_signal_watch(m_bus);

    gst_bin_add_many(GST_BIN(m_pipeline), m_videoSrc, m_capsfilter, m_rtpvrawpay, m_sink, NULL);

    if (!gst_element_link_many(m_videoSrc, m_capsfilter, m_rtpvrawpay, m_sink, NULL))
        throw std::runtime_error("Elements could not be linked.\n");

    m_completed = true;

    // g_signal_connect(G_OBJECT(bus), "message::error", G_CALLBACK(errorCallback), this);
    // g_signal_connect(G_OBJECT(bus), "message::eos", G_CALLBACK(eosCallback), this);
}

RtpPipeline::~RtpPipeline()
{
    stop();

    if (m_rtpvrawpay)
        gst_object_unref(m_rtpvrawpay);
}
