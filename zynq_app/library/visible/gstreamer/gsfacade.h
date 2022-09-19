#ifndef GSFACADE_H
#define GSFACADE_H

#include <vector>
#include <memory>

#include "pipelines/pipelinebase.h"

//! \brief Class for simplifying usage of GStreamer and created pipelines (facade design pattern)
class GsFacade
{
public:
    // PipelineEnum is used as flags - values need to be powers of two!
    enum PipelineEnum : uint8_t { NONE = 0, RAW_SAVE = 1, RAW_RTP = 2, RAW_DISPLAY = 4, THERE_WILL_BE_NEXT = 8};

    GsFacade();
    ~GsFacade();

    bool initAndStart(PipelineEnum pipeline);
    void stop(PipelineEnum pipeline);

    bool setState(PipelineEnum pipeline, bool state);

    static void initIntervideoPipeline();

    /*!
     * \brief Standard GstElement creation with added logging
     */
    static GstElement* makeElement(const gchar *factoryName, const gchar *name);

private:
    // NOTE prob would move to settings
    static const int DEBUG_LEVEL = 2;

    std::unique_ptr<PipelineBase> rtpPipe;
    std::unique_ptr<PipelineBase> rawPipe;
    std::unique_ptr<PipelineBase> displayPipe;

    static bool m_interpipelineInited;
};

inline GsFacade::PipelineEnum operator|(GsFacade::PipelineEnum a, GsFacade::PipelineEnum b)
{
    return static_cast<GsFacade::PipelineEnum>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

#endif // GSFACADE_H
