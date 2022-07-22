#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "global/constans.h"
#include <string>
#include <gst/gst.h>

class RawFilePipeline
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

    void start_video();
    void stop_video();

    RawFilePipeline(const RawFilePipeline &pipeline) = delete;
    RawFilePipeline(RawFilePipeline &&pipeline) = delete;
    RawFilePipeline operator =(const RawFilePipeline &pipeline) = delete;
    RawFilePipeline operator =(RawFilePipeline &&pipeline) = delete;

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

#endif // RAWFILEPIPELINE_H
