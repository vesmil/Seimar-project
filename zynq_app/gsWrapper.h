#ifndef GSWRAPPER_H
#define GSWRAPPER_H

#include "gst/gst.h"
#include "pipelines/intersinkPipeline.h"

struct GsWrapper
{
    static void init();
    static void deinit();

    static GstElement* makeElement(const gchar *factoryname, const gchar *name);
    static GstCaps* makeDefualtCaps();

    static const gchar* getIntervideoChannel();

private:
    static void initIntervideoPipeline();

    static const char* m_intervideoName;
    static bool m_interpipelineInited;
};

#endif // GSWRAPPER_H
