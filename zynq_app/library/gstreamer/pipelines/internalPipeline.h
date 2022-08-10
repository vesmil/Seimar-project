#ifndef INTERNALPIPELINE_H
#define INTERNALPIPELINE_H

#include "pipelineBase.h"

/*!
 * \brief Complete pipeline transfaring data from vl42src to intervideosink
 */
class InternalPipeline : public PipelineBase
{
public:
    static InternalPipeline& getInstance();

private:
    void setSource(const gchar *name);
    void setSink(const gchar *name);
    void completePipeline();

    InternalPipeline();
};

#endif // INTERNALPIPELINE_H
