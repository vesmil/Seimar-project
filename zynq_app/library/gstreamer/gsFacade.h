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
    enum PipelineEnum : uint8_t { NONE = 0, RAW_SAVE = 1, RAW_RTP = 2, RAW_DISPLAY = 4 };

    GsFacade();
    ~GsFacade();

    void initAndStart(PipelineEnum pipeline);
    void stop(PipelineEnum pipeline);

private:
    std::unique_ptr<PipelineBase> rtpPipe;
    std::unique_ptr<PipelineBase> rawPipe;
    std::unique_ptr<PipelineBase> displayPipe;
};

inline GsFacade::PipelineEnum operator|(GsFacade::PipelineEnum a, GsFacade::PipelineEnum b)
{
    return static_cast<GsFacade::PipelineEnum>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

#endif // GSFACADE_H
