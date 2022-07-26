#include "gsWrapper.h"

#include <stdexcept>
#include <string>

#include "global/config.h"

#include <pipelines/intersinkPipeline.h>

const char* GstWrapper::m_intervideoName = "interchannel";
bool GstWrapper::m_intervideopiPelineSetup = false;

void GstWrapper::init()
{
    gst_init(nullptr, nullptr);
    // setenv("GST_DEBUG", ("*:" + std::to_string(3)).c_str(), 1);

    initIntervideoPipeline();
}

void GstWrapper::deinit()
{
    gst_deinit();
}

void GstWrapper::initIntervideoPipeline()
{
    intersinkPipeline::getInstance();  // TODO store the instance better way

    m_intervideopiPelineSetup = true;
}

GstElement* GstWrapper::makeElement(const gchar *factoryname, const gchar *name)
{
    using namespace std::literals;

    GstElement *res = gst_element_factory_make(factoryname, name);
    if (!res)
        throw std::runtime_error("Can't instantiate element "s + name + " of type " + factoryname + ")");

    return res;
}

const gchar* GstWrapper::getIntervideoChannel()
{
    return m_intervideoName;
}

GstElement* GstWrapper::makeIntersource(const gchar* name)
{
    if (!m_intervideopiPelineSetup)
        gst_printerr("Intervideosrc request without initialized intervideo pipeline");

    GstElement* src = GstWrapper::makeElement("intervideosrc", name);
    g_object_set(src,"channel", getIntervideoChannel, NULL);

    return src;
}

GstCaps* GstWrapper::makeDefualtCaps()
{
    return gst_caps_new_simple("video/x-raw",
                "format", G_TYPE_STRING, "RGB",
                "framerate", GST_TYPE_FRACTION, 60, 1,
                "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
                "width", G_TYPE_INT, glb::dim::WIDTH,
                "height", G_TYPE_INT, glb::dim::HEIGHT,
                               NULL);
}

