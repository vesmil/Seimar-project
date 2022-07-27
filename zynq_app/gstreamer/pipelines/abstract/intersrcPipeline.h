#ifndef INTERSINKPIPELINE_H
#define INTERSINKPIPELINE_H

#include "pipeline.h"

/*!
 * \brief Pipeline which uses data from intervideosrc
 */
class IntersrcPipeline : public Pipeline
{
protected:
    IntersrcPipeline() = default;

    void setSource(const gchar *name);
};

#endif // INTERSINKPIPELINE_H
