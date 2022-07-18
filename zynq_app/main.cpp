#include <QCoreApplication>

#include "pipeline.h"
#include "global/constans.h"

#include <gst/gst.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    gst_init (&argc, &argv);

    GstElement *pipeline = gst_pipeline_new("pipeline");
    GstBus *bus = gst_element_get_bus(pipeline);

    GstElement *videosrc = gst_element_factory_make("v4l2src", "videosrc");
    g_object_set(videosrc,
                 "device", glb::constants::VIDEO_SRC_PATH.c_str(),
                 "io-mode", 4,
                 "do-timestamp", TRUE,
                 NULL);

    GstCaps *videoCaps {gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB",
            "framerate", GST_TYPE_FRACTION, 60, 1,
            "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
            "width", G_TYPE_INT, glb::constants::WIDTH,
            "height", G_TYPE_INT, glb::constants::HEIGHT,
            NULL)};

    GstElement *appsink = gst_element_factory_make("appsink", "appsink");
    g_object_set(appsink, "caps", videoCaps, "emit-signals", TRUE, NULL);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, appsink, NULL);

    /* Free resources */
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);

    return a.exec();
}
