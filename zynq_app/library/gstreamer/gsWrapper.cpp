#include "gsWrapper.h"

#include <stdexcept>
#include <string>
#include "global/config.h"

const char* GsWrapper::m_intervideoChannelName = "interchannel";
bool GsWrapper::m_interpipelineInited = false;

void GsWrapper::init(int debug)
{
    gst_init(nullptr, nullptr);

    if (debug > 0) {
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
    IntersinkPipeline::getInstance().start();
    m_interpipelineInited = true;
}

GstElement* GsWrapper::makeElement(const gchar *factoryname, const gchar *name)
{
    using namespace std::literals;

    GstElement *res = gst_element_factory_make(factoryname, name);
    if (!res)
        throw std::runtime_error("Can't instantiate element "s + name + " of type " + factoryname + ")");
    return res;
}

const gchar* GsWrapper::getDefaultIntervidChanName()
{
    return m_intervideoChannelName;
}

GstCaps* GsWrapper::makeDefualtCaps()
{
    return gst_caps_new_simple("video/x-raw",
                "format", G_TYPE_STRING, "RGB",
                "framerate", GST_TYPE_FRACTION, 60, 1,
                "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
                "width", G_TYPE_INT, glb::dim::WIDTH,
                "height", G_TYPE_INT, glb::dim::HEIGHT, NULL);
}

