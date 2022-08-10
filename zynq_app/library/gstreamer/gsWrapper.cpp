#include "gsWrapper.h"

#include <string>

#include "global/logCategories.h"
#include "global/config.h"

bool GsWrapper::m_interpipelineInited = false;

void GsWrapper::init()
{
    gst_init(nullptr, nullptr);

    if (DEBUG_LEVEL > 0) {
        gst_debug_set_active(TRUE);
        gst_debug_set_default_threshold(GST_LEVEL_FIXME);
    }

    initIntervideoPipeline();
}

void GsWrapper::deinit()
{
    gst_deinit();
}

void GsWrapper::initIntervideoPipeline()
{
    InternalPipeline::getInstance().start();
    m_interpipelineInited = true;
}

GstElement* GsWrapper::makeElement(const gchar *factoryName, const gchar *name)
{
    GstElement *res = gst_element_factory_make(factoryName, name);
    qCWarning(gsLog()) << "Element" << name << "of type" << factoryName << (res? "created successfully" : "could not be created.");
    return res;
}
