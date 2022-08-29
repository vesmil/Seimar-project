#ifndef GSFACADE_H
#define GSFACADE_H

#include <vector>
#include <memory>

#include "pipelines/pipelinebase.h"

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

    static void initIntervideoPipeline();

    /*!
     * \brief Standard GstElement creation with added logging
     */
    static GstElement* makeElement(const gchar *factoryName, const gchar *name);

private:
    std::unique_ptr<PipelineBase> rtpPipe;
    std::unique_ptr<PipelineBase> rawPipe;
    std::unique_ptr<PipelineBase> displayPipe;

    static bool m_interpipelineInited;

    static const int DEBUG_LEVEL = 3;
};

inline GsFacade::PipelineEnum operator|(GsFacade::PipelineEnum a, GsFacade::PipelineEnum b)
{
    return static_cast<GsFacade::PipelineEnum>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

#endif // GSFACADE_H
