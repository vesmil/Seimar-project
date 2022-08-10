#ifndef GSWRAPPER_H
#define GSWRAPPER_H

#include <gst/gst.h>
#include "pipelines/internalPipeline.h"

/*!
 * \brief Wrapper adding improved debugging capabilities and internal pipeline for splitting source
 */
struct GsWrapper
{
    static void init();
    static void deinit();

    /*!
     * \brief Standard GstElement creation with added logging
     */
    static GstElement* makeElement(const gchar *factoryName, const gchar *name);

private:
    static void initIntervideoPipeline();

    static bool m_interpipelineInited;

    static const int WIDTH = 1024;
    static const int HEIGHT = 768;

    static const int DEBUG_LEVEL = 3;
};

#endif // GSWRAPPER_H
