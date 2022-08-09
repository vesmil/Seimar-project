#ifndef GSWRAPPER_H
#define GSWRAPPER_H

#include "gst/gst.h"
#include "pipelines/intersinkPipeline.h"

/*!
 * \brief Wrapper adding default elements and improved debugging capabilities
 */
struct GsWrapper
{
    static void init(int debug = 0);
    static void deinit();

    static GstElement* makeElement(const gchar *factoryname, const gchar *name);
    static GstCaps* makeDefualtCaps();

    static const gchar* getDefaultIntervidChanName();

private:
    static void initIntervideoPipeline();

    static const char* m_intervideoChannelName;
    static bool m_interpipelineInited;
};

#endif // GSWRAPPER_H
