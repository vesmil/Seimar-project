#ifndef GSFACADE_H
#define GSFACADE_H

#include <vector>
#include <memory>

#include "pipelines/abstract/pipeline.h"

/*!
 * \brief Facade design pattern simplifying usage of GStreamer and created pipelines
 */
class GsFacade
{
public:
    enum PipelineEnum {
        NONE = 0,
        RAW = 1,
        RTP = 2,
        DP = 4
    };

    GsFacade();
    ~GsFacade();

    void initAndStart(PipelineEnum pipeline);
    void stop(PipelineEnum pipeline);

private:
    Pipeline* rtpPipe = nullptr;
    Pipeline* rawPipe = nullptr;
    // ...
};

inline enum GsFacade::PipelineEnum operator|(GsFacade::PipelineEnum a, GsFacade::PipelineEnum b)
{
    return static_cast<GsFacade::PipelineEnum>(static_cast<int>(a) | static_cast<int>(b));
}

#endif // GSFACADE_H
