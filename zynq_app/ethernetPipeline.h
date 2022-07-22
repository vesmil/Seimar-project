#ifndef ETHERNETPIPELINE_H
#define ETHERNETPIPELINE_H

#include "global/constans.h"
#include <gst/gst.h>

class EthernetPipeline
{
public:
    EthernetPipeline();
    ~EthernetPipeline();

    void start_broadcast();
    void stop_broadcast();

    EthernetPipeline(const EthernetPipeline &pipeline) = delete;
    EthernetPipeline(EthernetPipeline &&pipeline) = delete;
    EthernetPipeline operator =(const EthernetPipeline &pipeline) = delete;
    EthernetPipeline operator =(EthernetPipeline &&pipeline) = delete;

private:
    GstElement *videosrc, *capsfilter, *rtpvrawpay, *udpsink, *pipeline;
    GstCaps *videoCaps;
    GstBus *bus;

    void set_source();
    void set_caps_filter();
    void set_rtp_payload();
    void set_udpsink();
    void set_pipeline();

    void unref_all();
};

#endif // ETHERNETPIPELINE_H
