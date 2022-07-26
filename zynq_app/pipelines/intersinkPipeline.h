#ifndef INTERSINKPIPELINE_H
#define INTERSINKPIPELINE_H

#include "pipeline.h"

class intersinkPipeline : Pipeline
{
public:
    static intersinkPipeline* getInstance();

    void start();
    void stop();

private:
    void setSource(const gchar *name);
    void setSink(const gchar *name);

    intersinkPipeline();
    ~intersinkPipeline();
};

#endif // INTERSINKPIPELINE_H
