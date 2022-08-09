#ifndef RTPPIPELINE_H
#define RTPPIPELINE_H

#include "abstract/intersrcPipeline.h"

/*!
 * \brief Complete pipeline sending data from interpipelinesrc to IP address in config.h using RTP
 */
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
