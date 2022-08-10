#ifndef GSFACADE_H
#define GSFACADE_H

#include <vector>
#include <memory>

#include "pipelines/pipelineBase.h"

/*!
 * \brief Class for simplifying usage of GStreamer and created pipelines (facade design pattern)
 */
class GsFacade
{
public:
    enum PipelineEnum : uint8_t { NONE = 0, RAW_SAVE = 1, RAW_RTP = 2, DISP_PORT = 4 };

    GsFacade();
    ~GsFacade();

    void initAndStart(PipelineEnum pipeline);
    void stop(PipelineEnum pipeline);

private:
    std::unique_ptr<PipelineBase> rtpPipe;
    std::unique_ptr<PipelineBase> rawPipe;
    std::unique_ptr<PipelineBase> hdmiPipe;
};

#endif // GSFACADE_H
