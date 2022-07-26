#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst/gst.h>

class Pipeline
{
public:
    void start();
    void stop();

    ~Pipeline();

protected:
    Pipeline();

    void setCapsFilter(const gchar *name);
    void unrefAll();

    GstElement *m_videoSrc, *m_capsfilter, *m_sink, *m_pipeline;
    GstCaps *m_videoCaps;
    GstBus *m_bus;

    bool m_completed;
};

#endif // PIPELINE_H
