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
    delete rawPipe;
    delete rtpPipe;

    GsWrapper::deinit();
}

void GsFacade::initAndStart(PipelineEnum pipelineEnum)
{
    if (pipelineEnum & RAW)
    {
        rawPipe = new RawFilePipeline();
        rawPipe->start();
    }

    if (pipelineEnum & RTP)
    {
        rtpPipe = new RtpPipeline();
        rtpPipe->start();
    }
}

void GsFacade::stop(PipelineEnum pipelineEnum)
{
    if (pipelineEnum & RAW && rawPipe)
    {
        rawPipe ->stop();
    }

    if (pipelineEnum & RTP && rtpPipe)
    {
        rtpPipe ->stop();
    }
}
