#ifndef INTERSINKPIPELINE_H
#define INTERSINKPIPELINE_H

#include "pipelineBase.h"

/*!
 * \brief Pipeline which uses data from intervideosrc
 */
class PipelineFromInternSrc : public PipelineBase
{
protected:
    PipelineFromInternSrc() = default;

    void setSource(const gchar *name);
};

#endif // INTERSINKPIPELINE_H
