#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst/gst.h>

// TODO make inheritance more obvious...

/*!
 * \brief Abstract Pipeline class with basic pipeline attributes
 */
class Pipeline
{
public:
    void start();
    void stop();

    ~Pipeline();

    // Disable copy constructors for all pipelines (pipeline subclasses)
    Pipeline(const Pipeline&) = delete;
    Pipeline& operator =(const Pipeline&) = delete;

protected:
    // Only subclassses can construct pipeline
    //  - it's missing key elements which needs to be added
    Pipeline() = default;

    void setCapsFilter(const gchar *name);

    GstElement *m_videoSrc, *m_capsfilter, *m_sink, *m_pipeline;
    GstCaps *m_videoCaps;
    GstBus *m_bus;

    bool m_completed;
};

#endif // PIPELINE_H
