#ifndef GSWRAPPER_H
#define GSWRAPPER_H

#include "gst/gst.h"

struct GstWrapper
{
    static void init();
    static void deinit();

    static GstElement* makeElement(const gchar *factoryname, const gchar *name);

    static GstElement* makeIntersource(const gchar* name);
    static GstCaps* makeDefualtCaps();

    static const gchar* getIntervideoChannel();

private:
    static void initIntervideoPipeline();

    static const char* m_intervideoName;
    static bool m_intervideopiPelineSetup;
};

#endif // GSWRAPPER_H
