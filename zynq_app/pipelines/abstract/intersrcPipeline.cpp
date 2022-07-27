#include "intersrcPipeline.h"

#include <gsWrapper.h>
#include <stdexcept>

void IntersrcPipeline::setSource(const gchar* name)
{
    m_videoSrc = GsWrapper::makeIntersource(name);
}
