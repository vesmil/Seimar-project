#include "gsFacade.h"

#include "pipelines/rtpPipeline.h"
#include "pipelines/rawFilePipeline.h"

#include "gsWrapper.h"
#include "global/logCategories.h"

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
        qCWarning(gsLog()) << "Initializing and starting storage of RAW stream";
        rawPipe = new RawFilePipeline();
        rawPipe->start();
    }

    if (pipelineEnum & RTP)
    {
        qCWarning(gsLog()) << "Initializing and starting RTP stream";
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
