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
    m_data.sink = GsFacade::makeElement("kmssink", "kmssink");
    // g_object_set(m_data.sink, "bus-id", "fd4a0000.display", "fullscreen-overlay", 1, NULL);
    g_object_set(m_data.sink, "bus-id", "a0000000.v_mix", "plane-id", 37 ,"fullscreen-overlay", 0, "sync", 0, NULL); //  "render-rectangle", "<0,0,1920,1080>",
}

RawDisplayPipeline::~RawDisplayPipeline()
{
    stop();
}
