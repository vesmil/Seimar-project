#ifndef INTERSINKPIPELINE_H
#define INTERSINKPIPELINE_H

#include "abstract/pipeline.h"

class IntersinkPipeline : public Pipeline
{
public:
    static IntersinkPipeline& getInstance();

private:
    void setSource(const gchar *name);
    void setSink(const gchar *name);
    void completePipeline();

    IntersinkPipeline();
};

#endif // INTERSINKPIPELINE_H
