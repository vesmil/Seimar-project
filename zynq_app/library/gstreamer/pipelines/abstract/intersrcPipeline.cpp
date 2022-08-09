#include "intersrcPipeline.h"

#include <stdexcept>
#include "library/gstreamer/gsWrapper.h"

void IntersrcPipeline::setSource(const gchar* name)
{
    m_videoSrc = GsWrapper::makeElement("intervideosrc", name);
    g_object_set(m_videoSrc,"channel", GsWrapper::getDefaultIntervidChanName(), NULL);
}
