#include "rawFilePipeline.h"

#include <stdexcept>

RawFilePipeline::RawFilePipeline() : PipelineBase()
{
    set_filesink();
    complete_pipeline();
}

void RawFilePipeline::set_filesink()
{
    sink = gst_element_factory_make("filesink", "sink");
    g_object_set(sink, "location", glb::path::VIDEO_OUT.c_str(), NULL);
}

void RawFilePipeline::complete_pipeline()
{
    pipeline = gst_pipeline_new("pipeline");
    bus = gst_element_get_bus(pipeline);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, sink, NULL);

    if (!gst_element_link_many(videosrc, capsfilter, sink, NULL))
    {
        throw std::runtime_error("Elements could not be linked.\n");
    }
    else
    {
        completed = true;
    }
}

RawFilePipeline::~RawFilePipeline()
{
    stop();
    gst_deinit();
}
