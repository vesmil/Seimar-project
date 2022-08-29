#include "rawdisplaypipeline.h"

#include "library/visible/gstreamer/gsfacade.h"

RawDisplayPipeline::RawDisplayPipeline()
{
    setSrcFromInternalPipeline("display-source");
    setDefaultCapsFilter("display-caps");
    setKmssink();
    completePipeline("display-pipeline");
}

void RawDisplayPipeline::setKmssink()
{
    // m_data.sink = GsWrapper::makeElement("kmssink", "kmssink");
    // g_object_set(m_data.sink, "fullscreen-overlay", 1, nullptr);

    m_data.sink = GsFacade::makeElement("autovideosink", "display-autovideosink");
}

RawDisplayPipeline::~RawDisplayPipeline()
{
    stop();
}
