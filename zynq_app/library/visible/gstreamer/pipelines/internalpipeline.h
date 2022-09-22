#ifndef INTERNALPIPELINE_H
#define INTERNALPIPELINE_H

#include "pipelinebase.h"

/*!
 * \brief Singleton pipeline for transferring data from vl42src to intervideosink used by other pipelines (to allow spliting)
 */
class InternalPipeline : public PipelineBase
{
public:
    static InternalPipeline& getInstance();

    /*!
     * \brief Return the name of the channel used for intervideosrc
     * \detail The app uses intervideo pipeline to allow multiple pipeline from same source
     */
    static const gchar* getChannelName();

private:
    InternalPipeline();

    static const gchar* m_intervideoChannelName;

    GstPad* caps;

    void setSource(const gchar *name);
    void setSink(const gchar *name);
    void completePipeline();
};

#endif // INTERNALPIPELINE_H
