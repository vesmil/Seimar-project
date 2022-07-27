#ifndef RTPPIPELINE_H
#define RTPPIPELINE_H

#include "abstract/intersrcPipeline.h"

class RtpPipeline : public IntersrcPipeline
{
public:
    RtpPipeline();
    ~RtpPipeline();

private:
    GstElement *m_rtpvrawpay;

    void setRtpPayload();
    void setUdpsink();
    void completePipeline();
};

#endif // RTPPIPELINE_H
