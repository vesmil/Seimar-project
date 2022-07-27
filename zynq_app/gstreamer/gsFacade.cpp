#include "gsFacade.h"

#include "pipelines/rtpPipeline.h"
#include "pipelines/rawFilePipeline.h"
#include "gsWrapper.h"

GsFacade::GsFacade()
{
    GsWrapper::init();
}

GsFacade::~GsFacade()
{
    GsWrapper::deinit();
}

void GsFacade::start(PipelineEnum pipelineEnum)
{
    if (pipelineEnum & RAW)
    {
        m_pipelineVector.emplace_back(std::make_unique<RawFilePipeline>());
        m_pipelineVector.back()->start();
    }

    if (pipelineEnum & RTP)
    {
        m_pipelineVector.emplace_back(std::make_unique<RtpPipeline>());
        m_pipelineVector.back()->start();
    }
}

