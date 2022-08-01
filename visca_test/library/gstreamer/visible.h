#ifndef VISIBLE_H
#define VISIBLE_H

#include <gst/gst.h>
#include <string>

class Visible
{
public:
    Visible();

private:
    struct {
        GstElement *pipeline, *source, *queue, *capsfilter, *transform, *enc, *parse, *rtph264pay, *udpsink;
        GstCaps *caps = nullptr;
    } streamData;

    static bool isMxcVideo(const std::string &name);
};

#endif // VISIBLE_H
