#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "abstract/intersrcPipeline.h"

class RawFilePipeline : public IntersrcPipeline
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

private:
    void setFilesink();
    void completePipeline();
};

#endif // RAWFILEPIPELINE_H
