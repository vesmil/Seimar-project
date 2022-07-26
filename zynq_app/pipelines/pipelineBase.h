#ifndef PIPELINEBASE_H
#define PIPELINEBASE_H

#include "global/constans.h"
#include <gst/gst.h>

class PipelineBase
{
public:
    ~PipelineBase();

    void start();
    void stop();

protected:
    PipelineBase();

    void unrefAll();

    void setSource(const gchar *name);
    void setCapsFilter(const gchar *name);

    GstElement *m_videoSrc, *m_capsfilter, *m_sink, *m_pipeline;
    GstCaps *m_videoCaps;
    GstBus *m_bus;

    bool m_completed;
};

#endif // PIPELINEBASE_H
