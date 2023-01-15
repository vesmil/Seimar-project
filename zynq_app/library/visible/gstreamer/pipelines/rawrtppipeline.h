#ifndef RAWRTPPIPELINE_H
#define RAWRTPPIPELINE_H

#include "pipelinebase.h"

/*!
 * \brief Complete pipeline - sending data from interpipelinesrc to IP address in config.h using RTP
 */
class RawRtpPipeline : public Pipelinebase
{
public:
    RawRtpPipeline();
    ~RawRtpPipeline();

private:
    struct
    {
        GstElement *rtpvrawpay = nullptr;
    } m_rtp_data;

    void setRtpPayload();
    void setUdpsink();
    void completePipeline();
};

#endif // RAWRTPPIPELINE_H
