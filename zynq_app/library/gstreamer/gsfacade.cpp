#include "gsfacade.h"

#include "pipelines/rawrtppipeline.h"
#include "pipelines/rawfilepipeline.h"
#include "pipelines/rawdisplaypipeline.h"

#include "gswrapper.h"
#include "global/logcategories.h"

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
        qCInfo(gsLog()) << "Initializing and starting storage of RAW stream";
        rawPipe = std::make_unique<RawFilePipeline>();
        rawPipe->start();
    }

    if (pipelineEnum & RAW_RTP)
    {
        qCInfo(gsLog()) << "Initializing and starting stream of RAW data over RTP";
        rtpPipe =  std::make_unique<RawRtpPipeline>();
        rtpPipe->start();
    }

    if (pipelineEnum & RAW_DISPLAY)
    {
        qCInfo(gsLog()) << "Initializing and starting Display port stream";
        displayPipe =  std::make_unique<RawDisplayPipeline>();
        displayPipe->start();
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

    if (pipelineEnum & RAW_DISPLAY && displayPipe)
    {
        displayPipe ->stop();
    }
}
