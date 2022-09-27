#ifndef RAWDISPLAYPIPELINE_H
#define RAWDISPLAYPIPELINE_H

#include "pipelinebase.h"

/*!
 * \brief Complete pipeline - displaying raw data
 */
class RawDisplayPipeline : public PipelineBase
{
public:
    RawDisplayPipeline();
    ~RawDisplayPipeline();

private:
    struct
    {
        GstElement *videoconvert = nullptr, *videoscale = nullptr;
    } m_displayData;

    void setVideoconvert();
    void setVideoscale();
    // void setMixerCaps();
    void setKmssink();
    void completePipeline(const gchar *name);
};

#endif // RAWDISPLAYPIPELINE_H
