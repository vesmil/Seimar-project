#include "ethernetPipeline.h"

#include <stdexcept>
#include <thread>

EthernetPipeline::EthernetPipeline()
{
    set_rtp_payload();
    set_udpsink();
    complete_pipeline();
}

void EthernetPipeline::set_rtp_payload()
{
    rtpvrawpay = gst_element_factory_make("rtpvrawpay", "rtpvrawpay");
}

void EthernetPipeline::set_udpsink()
{
    sink = gst_element_factory_make("udpsink", "sink");

    g_object_set(sink, "port", 9002, NULL);
    g_object_set(sink, "host", glb::path::IP_ADDRESS.c_str(), NULL);
}

void EthernetPipeline::complete_pipeline()
{
    pipeline = gst_pipeline_new("pipeline");
    bus = gst_element_get_bus(pipeline);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, rtpvrawpay, sink, NULL);

    if (!gst_element_link_many(videosrc, capsfilter, rtpvrawpay, sink, NULL))
    {
        throw std::runtime_error("Elements could not be linked.\n");
    }

    bus = gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);

    // g_signal_connect(G_OBJECT(bus), "message::error", G_CALLBACK(errorCallback), this);
    // g_signal_connect(G_OBJECT(bus), "message::eos", G_CALLBACK(eosCallback), this);
}

void EthernetPipeline::start()
{
    // TODO test completion

    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void EthernetPipeline::stop()
{
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

EthernetPipeline::~EthernetPipeline()
{
    stop();
    unref_all();
    gst_deinit();
}

void EthernetPipeline::unref_all()
{
    if (rtpvrawpay)
        gst_object_unref(rtpvrawpay);
}
