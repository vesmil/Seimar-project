#ifndef PIPELINE_H
#define PIPELINE_H

#include <string>

class Pipeline
{
public:
    Pipeline(const std::string& src);
    Pipeline(const Pipeline &pipeline) = delete;
    Pipeline(Pipeline &&pipeline) = delete;
    Pipeline operator =(const Pipeline &pipeline) = delete;
    Pipeline operator =(Pipeline &&pipeline) = delete;

private:
    const std::string videoSrcPath;

};

#endif // PIPELINE_H
