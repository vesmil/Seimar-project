#ifndef GSWRAPPER_H
#define GSWRAPPER_H

#include "gst/gst.h"

class GSWrapper
{
public:
    static GstElement* makeElement(const gchar *factoryname, const gchar *name);
};

#endif // GSWRAPPER_H
