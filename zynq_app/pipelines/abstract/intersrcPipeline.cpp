#include "intersrcPipeline.h"

#include <gsWrapper.h>
#include <stdexcept>

void IntersrcPipeline::setSource(const gchar* name)
{
    m_videoSrc = GsWrapper::makeElement("intervideosrc", name);
    g_object_set(m_videoSrc,"channel", GsWrapper::getIntervideoChannel(), NULL);
}
