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
    GstElement *videosrc, *capsfilter, *sink, *pipeline;
    GstCaps *videoCaps;
    GstBus *bus;

    void unref_all();
};

#endif // PIPELINE_H
