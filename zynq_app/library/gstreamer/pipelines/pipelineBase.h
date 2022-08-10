#ifndef PIPELINEBASE_H
#define PIPELINEBASE_H

#include <gst/gst.h>

/*!
 * \brief Abstract Pipeline class with basic pipeline attributes
 */
class PipelineBase
{
public:
    void start();
    void stop();

    ~PipelineBase();

    // Disable copy constructors for all pipelines (pipeline subclasses)
    PipelineBase(const PipelineBase&) = delete;
    PipelineBase& operator =(const PipelineBase&) = delete;

protected:
    PipelineBase() = default;

    void setCapsFilter(const gchar *name);

    GstElement *m_videoSrc, *m_capsfilter, *m_sink, *m_pipeline;
    GstCaps *m_videoCaps;
    GstBus *m_bus;

    bool m_completed;
};

#endif // PIPELINEBASE_H
