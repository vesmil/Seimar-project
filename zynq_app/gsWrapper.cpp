#include "gsWrapper.h"

#include <stdexcept>
#include <string>

#include "global/config.h"

const char* GsWrapper::m_intervideoName = "interchannel";
bool GsWrapper::m_interpipelineInited = false;

void GsWrapper::init()
{
    gst_init(nullptr, nullptr);
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

// TODO move
const gchar* GsWrapper::getIntervideoChannel()
{
    return m_intervideoName;
}

GstElement* GsWrapper::makeIntersource(const gchar* name)
{
    if (!m_interpipelineInited)
        gst_printerr("Intervideosrc request without initialized intervideo pipeline");

    GstElement* src = GsWrapper::makeElement("intervideosrc", name);
    g_object_set(src,"channel", getIntervideoChannel, NULL);

    return src;
}

GstCaps* GsWrapper::makeDefualtCaps()
{
    return gst_caps_new_simple("video/x-raw",
                "format", G_TYPE_STRING, "RGB",
                "framerate", GST_TYPE_FRACTION, 30, 1,
                "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
                "width", G_TYPE_INT, glb::dim::WIDTH,
                "height", G_TYPE_INT, glb::dim::HEIGHT, NULL);
}

