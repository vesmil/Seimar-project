#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "pipelinebase.h"

/*!
 * \brief Complete pipeline - saving raw data from interpipelinesrc
 */
class RawFilePipeline : public Pipelinebase
{
public:
    RawFilePipeline();
    ~RawFilePipeline();

private:
    void setFilesink();
};

#endif // RAWFILEPIPELINE_H
