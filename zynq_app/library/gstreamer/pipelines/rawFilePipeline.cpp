#include "rawFilePipeline.h"

#include "global/config.h"
#include "global/logCategories.h"

#include "../gsWrapper.h"

RawFilePipeline::RawFilePipeline() : PipelineBase()
{
    setSrcFromInternalPipeline("inter-file-source");
    setDefaultCapsFilter("file-caps");
    setFilesink();
    completePipeline("file-pipeline");
}

void RawFilePipeline::setFilesink()
{
    m_data.sink = GsWrapper::makeElement("filesink", "file-sink");
    g_object_set(m_data.sink, "location", glb::path::VIDEO_OUT.c_str(), nullptr);
}

RawFilePipeline::~RawFilePipeline()
{
    stop();
}
