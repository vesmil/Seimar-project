#ifndef RTPPIPELINE_H
#define RTPPIPELINE_H

#include "intersrcPipeline.h"

class RtpPipeline : public IntersrcPipeline
{
public:
    RtpPipeline();
    ~RtpPipeline();

    RtpPipeline(const RtpPipeline&) = delete;
    RtpPipeline& operator =(const RtpPipeline&) = delete;

private:
    GstElement *m_rtpvrawpay;

    void setRtpPayload();
    void setUdpsink();
    void completePipeline();
};

#endif // RTPPIPELINE_H
