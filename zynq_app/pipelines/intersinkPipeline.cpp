#include "intersinkPipeline.h"

#include <gsWrapper.h>
#include "global/config.h"

intersinkPipeline *intersinkPipeline::getInstance()
{
    static intersinkPipeline* instance;
    return instance;
}

void intersinkPipeline::setSource(const gchar *name)
{
    m_videoSrc = GstWrapper::makeElement("v4l2src",name);
    g_object_set(m_videoSrc,"device", glb::path::VIDEO_SRC.c_str(),"do-timestamp", TRUE, NULL);
}

void intersinkPipeline::setSink(const gchar *name)
{
    m_sink = GstWrapper::makeElement("intervideosink",name);
    g_object_set(m_sink,"channel", GstWrapper::getIntervideoChannel(), NULL);
}


intersinkPipeline::intersinkPipeline()
{
    setSource("v4l2source");
}
