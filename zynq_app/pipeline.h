#ifndef PIPELINE_H
#define PIPELINE_H

#include <string>
#include <gst/gst.h>

#include "global/constans.h"

class Pipeline
{
public:
    Pipeline();

private:
    const std::string videoSrcPath;

};

#endif // PIPELINE_H
