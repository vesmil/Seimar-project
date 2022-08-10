#include "pipelineFromInternSrc.h"
#include "library/gstreamer/gsWrapper.h"

void PipelineFromInternSrc::setSource(const gchar* name)
{
    m_videoSrc = GsWrapper::makeElement("intervideosrc", name);
    g_object_set(m_videoSrc,"channel", GsWrapper::getDefaultIntervidChanName(), nullptr);
}
