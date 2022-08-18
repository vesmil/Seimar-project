#ifndef RAWDISPLAYPIPELINE_H
#define RAWDISPLAYPIPELINE_H

#include "pipelinebase.h"

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
