#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "intersrcPipeline.h"

class RawFilePipeline : public IntersrcPipeline
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

    RawFilePipeline(const RawFilePipeline&) = delete;
    RawFilePipeline& operator =(const RawFilePipeline&) = delete;

private:
    void setFilesink();
    void completePipeline();
};

#endif // RAWFILEPIPELINE_H
