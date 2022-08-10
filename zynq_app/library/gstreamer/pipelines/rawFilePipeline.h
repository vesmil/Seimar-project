#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "pipelineBase.h"

/*!
 * \brief Complete pipeline - saving raw data from interpipelinesrc
 */
class RawFilePipeline : public PipelineBase
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

private:
    void setFilesink();
};

#endif // RAWFILEPIPELINE_H
