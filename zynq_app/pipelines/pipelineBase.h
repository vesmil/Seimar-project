#ifndef PIPELINEBASE_H
#define PIPELINEBASE_H

#include "global/constans.h"
#include <gst/gst.h>

class PipelineBase
{
public:
    PipelineBase();
    ~PipelineBase();

    PipelineBase(const PipelineBase &pipeline) = delete;
    PipelineBase(PipelineBase &&pipeline) = delete;
    PipelineBase operator =(const PipelineBase &pipeline) = delete;
    PipelineBase operator =(PipelineBase &&pipeline) = delete;

    void start();
    void stop();

protected:
    void unref_all();

    GstElement *videosrc, *capsfilter, *sink, *pipeline;
    GstCaps *videoCaps;
    GstBus *bus;

    bool completed;

    void set_source(const gchar *name);
    void set_caps_filter(const gchar *name);
};

#endif // PIPELINEBASE_H
