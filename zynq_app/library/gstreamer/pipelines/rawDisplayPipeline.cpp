#include "rawDisplayPipeline.h"
#include "../gsWrapper.h"

RawDisplayPipeline::RawDisplayPipeline()
{
    setSrcFromInternalPipeline("rawsource");
    setDefaultCapsFilter("rawcaps");
    setKmssink();
    completePipeline("displaypipeline");
}

void RawDisplayPipeline::setKmssink()
{
    m_data.sink = GsWrapper::makeElement("kmssink", "kmssink");
    g_object_set(m_data.sink, "fullscreen-overlay", 1, nullptr);
}

RawDisplayPipeline::~RawDisplayPipeline()
{
    stop();
}
