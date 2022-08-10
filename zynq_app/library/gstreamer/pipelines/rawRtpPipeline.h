#ifndef RAWRTPPIPELINE_H
#define RAWRTPPIPELINE_H

#include "pipelineBase.h"

/*!
 * \brief Complete pipeline sending data from interpipelinesrc to IP address in config.h using RTP
 */
class RawRtpPipeline : public PipelineBase
{
public:
    RawRtpPipeline();
    ~RawRtpPipeline();

private:
    GstElement *m_rtpvrawpay;

    void setRtpPayload();
    void setUdpsink();
    void completePipeline();
};

#endif // RAWRTPPIPELINE_H
