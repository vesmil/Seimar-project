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
    GsWrapper::deinit();
}

void GsFacade::initAndStart(PipelineEnum pipelineEnum)
{
    if (pipelineEnum & RAW_SAVE)
    {
        qCWarning(gsLog()) << "Initializing and starting storage of RAW stream";
        rawPipe = std::make_unique<RawFilePipeline>();
        rawPipe->start();
    }

    if (pipelineEnum & RAW_RTP)
    {
        qCWarning(gsLog()) << "Initializing and starting stream of RAW data over RTP";
        rtpPipe =  std::make_unique<RtpPipeline>();
        rtpPipe->start();
    }

    if (pipelineEnum & DISP_PORT)
    {
        qCWarning(gsLog()) << "Initializing and starting Display port stream - not done yet";
        // rtpPipe =  std::make_unique<RtpPipeline>();
        rtpPipe->start();
    }
}

void GsFacade::stop(PipelineEnum pipelineEnum)
{
    if (pipelineEnum & RAW_SAVE && rawPipe)
    {
        rawPipe ->stop();
    }

    if (pipelineEnum & RAW_RTP && rtpPipe)
    {
        rtpPipe ->stop();
    }
}
