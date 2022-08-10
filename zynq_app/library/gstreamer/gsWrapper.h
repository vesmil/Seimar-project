#ifndef GSWRAPPER_H
#define GSWRAPPER_H

#include <gst/gst.h>
#include "pipelines/internalPipeline.h"

/*!
 * \brief Wrapper adding default elements and improved debugging capabilities
 */
struct GsWrapper
{
    static void init(int debug = 0);
    static void deinit();

    static GstElement* makeElement(const gchar *factoryname, const gchar *name);

    static const gchar* getDefaultIntervidChanName();

private:
    static void initIntervideoPipeline();

    static const char* m_intervideoChannelName;
    static bool m_interpipelineInited;

    static const int WIDTH = 1024;
    static const int HEIGHT = 768;
};

#endif // GSWRAPPER_H
