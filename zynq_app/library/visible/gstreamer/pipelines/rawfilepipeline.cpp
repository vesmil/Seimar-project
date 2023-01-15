#include "rawfilepipeline.h"

#include "global/logcategories.h"
#include "library/visible/gstreamer/gsfacade.h"
#include "library/application/settings.h"

RawFilePipeline::RawFilePipeline() : Pipelinebase()
{
    setSrcFromInternalPipeline("inter-file-source");
    setDefaultCapsFilter("file-caps");
    setFilesink();
    completePipeline("file-pipeline");
}

void RawFilePipeline::setFilesink()
{
    m_data.sink = GsFacade::makeElement("filesink", "file-sink");
    g_object_set(m_data.sink, "location", Settings::getInstance().path.videoOut.c_str(), nullptr);
}

RawFilePipeline::~RawFilePipeline()
{
    stop();
}
