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
    void completePipeline(const gchar *name);

    struct
    {
        GstElement *videoSrc = nullptr, *capsFilter = nullptr, *sink = nullptr, *pipeline = nullptr;
        GstCaps *videoCaps = nullptr;
        GstBus *bus = nullptr;
    } m_data;

    static const int WIDTH = 1024;
    static const int HEIGHT = 768;

    bool m_completed = false;
};

#endif // PIPELINEBASE_H
