#ifndef PIPELINEBASE_H
#define PIPELINEBASE_H

#include <gst/gst.h>

#include "global/logcategories.h"

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

    template <typename T, typename ...TElems >
    void addAndLink(T pipeline, TElems ... elements)
    {
        // TODO add null check
        gst_bin_add_many(GST_BIN(pipeline), elements ..., nullptr);

        if (!gst_element_link_many(elements ..., nullptr))
            qCWarning(gsLog()) << "Elements could not be linked.";
        else
            m_completed = true;
    }

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