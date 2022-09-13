#include "rawdisplaypipeline.h"

#include "library/visible/gstreamer/gsfacade.h"

// TODO consider merging all raw pipelines together

RawDisplayPipeline::RawDisplayPipeline()
{
    setSrcFromInternalPipeline("display-source");
    setDefaultCapsFilter("display-caps");
    setKmssink();
    completePipeline("display-pipeline");
}

void RawDisplayPipeline::setKmssink()
{
    // TODO ...
    // m_data.sink = GsFacade::makeElement("kmssink", "kmssink");
    // g_object_set(m_data.sink, "fullscreen-overlay", 1, nullptr);

    m_data.sink = GsFacade::makeElement("autovideosink", "display-autovideosink");
}

RawDisplayPipeline::~RawDisplayPipeline()
{
    stop();
}
