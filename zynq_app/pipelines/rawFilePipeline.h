#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "pipelineBase.h"

class RawFilePipeline : public PipelineBase
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

    void start();
    void stop();

    RawFilePipeline(const RawFilePipeline &pipeline) = delete;
    RawFilePipeline(RawFilePipeline &&pipeline) = delete;
    RawFilePipeline operator =(const RawFilePipeline &pipeline) = delete;
    RawFilePipeline operator =(RawFilePipeline &&pipeline) = delete;

private:
    void set_filesink();
    void complete_pipeline();
};

#endif // RAWFILEPIPELINE_H
