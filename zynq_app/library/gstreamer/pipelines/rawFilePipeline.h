#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "pipelineFromInternSrc.h"

/*!
 * \brief Complete pipeline saving raw data from interpipelinesrc
 */
class RawFilePipeline : public PipelineFromInternSrc
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

private:
    void setFilesink();
    void completePipeline();
};

#endif // RAWFILEPIPELINE_H
