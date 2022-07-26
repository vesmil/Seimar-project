#ifndef INTERSINKPIPELINE_H
#define INTERSINKPIPELINE_H

#include <gst/gst.h>

#include "global/config.h"
#include "pipeline.h"

class IntersrcPipeline : public Pipeline
{
protected:
    IntersrcPipeline() = default;
    void setSource(const gchar *name);
};

#endif // INTERSINKPIPELINE_H
