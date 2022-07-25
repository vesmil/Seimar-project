#include "rawFilePipeline.h"

#include <stdexcept>
#include <thread>

RawFilePipeline::RawFilePipeline() : PipelineBase()
{
    set_filesink();
    complete_pipeline();
}

void RawFilePipeline::set_filesink()
{
    sink = gst_element_factory_make("filesink", "sink");
    g_object_set(sink, "location", glb::path::OUT_PATH.c_str(), NULL);
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

void RawFilePipeline::start()
{
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void RawFilePipeline::stop()
{
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
    gst_element_change_state(pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
}

RawFilePipeline::~RawFilePipeline()
{
    stop();
    gst_deinit();
}
