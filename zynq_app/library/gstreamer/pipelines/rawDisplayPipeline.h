#ifndef RAWDISPLAYPIPELINE_H
#define RAWDISPLAYPIPELINE_H

#include "pipelineBase.h"

/*!
 * \brief Complete pipeline - displaying raw data
 */
class RawDisplayPipeline : public PipelineBase
{
public:
    RawDisplayPipeline();
    ~RawDisplayPipeline();

private:
    void setKmssink();
};

#endif // RAWDISPLAYPIPELINE_H
