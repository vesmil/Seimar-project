#ifndef GSFACADE_H
#define GSFACADE_H

#include <vector>
#include <memory>

#include "pipelines/pipelineBase.h"

/*!
 * \brief Facade design pattern simplifying usage of GStreamer and created pipelines
 */
class GsFacade
{
public:
    enum PipelineEnum : uint8_t { NONE = 0, RAW = 1, RTP = 2, DP = 4 };

    GsFacade();
    ~GsFacade();

    void initAndStart(PipelineEnum pipeline);
    void stop(PipelineEnum pipeline);

private:
    PipelineBase* rtpPipe = nullptr;
    PipelineBase* rawPipe = nullptr;
    // ...
};

#endif // GSFACADE_H
