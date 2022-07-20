#ifndef PIPELINE_H
#define PIPELINE_H

#include "global/constans.h"
#include <string>
#include <gst/gst.h>

class Pipeline
{
public:
    Pipeline();
    ~Pipeline();

    void start_video();
    void stop_video();

    Pipeline(const Pipeline &pipeline) = delete;
    Pipeline(Pipeline &&pipeline) = delete;
    Pipeline operator =(const Pipeline &pipeline) = delete;
    Pipeline operator =(Pipeline &&pipeline) = delete;

private:
    GstElement *videosrc, *capsfilter, *filesink, *pipeline;
    GstCaps *videoCaps;
    GstBus *bus;

    void set_source();
    void set_caps_filter();
    void set_filesink();
    void set_pipeline();

    void unref_all();
};

#endif // PIPELINE_H
