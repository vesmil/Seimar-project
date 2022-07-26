#include "gsWrapper.h"

#include <stdexcept>
#include <string>

#include "global/constans.h"

void GsWrapper::initialize()
{
    if (!gst_is_initialized())
    {
        gst_init(nullptr, nullptr);
    }

    setenv("GST_DEBUG", ("*:" + std::to_string(3)).c_str(), 1);
}

void GsWrapper::deinitialize()
{
    gst_deinit();
}

GstElement* GsWrapper::makeElement(const gchar *factoryname, const gchar *name)
{
    using namespace std::literals;

    GstElement *res = gst_element_factory_make(factoryname, name);
    if (!res)
        throw std::runtime_error("Can't instantiate element "s + name + " of type " + factoryname + ")");
    return res;
}
