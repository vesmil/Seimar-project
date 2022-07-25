#include "ethernetPipeline.h"

#include <stdexcept>

#include "gsWrapper.h"
#include <thread>

EthernetPipeline::EthernetPipeline()
{
    set_source("sourcertp");
    set_caps_filter("rtpcaps");
    set_rtp_payload();
    set_udpsink();
    complete_pipeline();
}

void EthernetPipeline::set_rtp_payload()
{
    rtpvrawpay = GSWrapper::makeElement("rtpvrawpay", "rtpvrawpay");
}

void EthernetPipeline::set_udpsink()
{
    sink = GSWrapper::makeElement("udpsink", "udpsink");

    g_object_set(sink, "port", glb::rtp::PORT, NULL);
    g_object_set(sink, "host", glb::rtp::IP_ADDRESS.c_str(), NULL);
}

void EthernetPipeline::complete_pipeline()
{
    pipeline = gst_pipeline_new("pipeline");
    bus = gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, rtpvrawpay, sink, NULL);

    if (!gst_element_link_many(videosrc, capsfilter, rtpvrawpay, sink, NULL))
    {
        throw std::runtime_error("Elements could not be linked.\n");
    }
    else
    {
        completed = true;
    }

    // g_signal_connect(G_OBJECT(bus), "message::error", G_CALLBACK(errorCallback), this);
    // g_signal_connect(G_OBJECT(bus), "message::eos", G_CALLBACK(eosCallback), this);
}

EthernetPipeline::~EthernetPipeline()
{
    stop();

    if (rtpvrawpay)
        gst_object_unref(rtpvrawpay);
}
