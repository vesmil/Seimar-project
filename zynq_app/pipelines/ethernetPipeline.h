#ifndef ETHERNETPIPELINE_H
#define ETHERNETPIPELINE_H

#include "pipelineBase.h"

class EthernetPipeline : public PipelineBase
{
public:
    EthernetPipeline();
    ~EthernetPipeline();

    void start();
    void stop();

    EthernetPipeline(const EthernetPipeline &pipeline) = delete;
    EthernetPipeline(EthernetPipeline &&pipeline) = delete;
    EthernetPipeline operator =(const EthernetPipeline &pipeline) = delete;
    EthernetPipeline operator =(EthernetPipeline &&pipeline) = delete;

private:
    GstElement *rtpvrawpay;

    void set_rtp_payload();
    void set_udpsink();
    void complete_pipeline();

    void unref_all();
};

#endif // ETHERNETPIPELINE_H
