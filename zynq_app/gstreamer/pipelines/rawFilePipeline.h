#ifndef RAWFILEPIPELINE_H
#define RAWFILEPIPELINE_H

#include "abstract/intersrcPipeline.h"

/*!
 * \brief Complete pipeline saving raw data from interpipelinesrc
 */
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
