#ifndef PIPELINEBASE_H
#define PIPELINEBASE_H

#include <gst/gst.h>

/*!
 * \brief Abstract Pipeline class with basic pipeline attributes
 */
class PipelineBase
{
public:
    void start() const;
    void stop() const;

    ~PipelineBase();

    // Disable copy constructors for all pipelines (pipeline subclasses)
    PipelineBase(const PipelineBase&) = delete;
    PipelineBase& operator =(const PipelineBase&) = delete;

protected:
    PipelineBase() = default;

    void setDefaultCapsFilter(const gchar *name);
    void setSrcFromInternalPipeline(const gchar *name);
    void checkResult(bool linkingResult);

    struct
    {
        GstElement *videoSrc, *capsFilter, *sink, *pipeline;
        GstCaps *videoCaps;
        GstBus *bus;
    } m_data;

    static const int WIDTH = 1024;
    static const int HEIGHT = 768;

    bool m_completed;
};

#endif // PIPELINEBASE_H
