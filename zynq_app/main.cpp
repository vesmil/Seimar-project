#include <QCoreApplication>
#include <mutex>
#include <thread>

#include "pipeline.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Inspiration
    // https://stackoverflow.com/questions/66550597/gstreamer-pipeline-from-cam-to-file-c-code-ends-up-with-empty-output-file

    if (!gst_is_initialized()) {
        // setenv("GST_DEBUG", ("*:" + std::to_string(3)).c_str(), 1);
        gst_init(nullptr, nullptr);
    }

    GstElement *videosrc, *capsfilter, *sink, *pipeline;
    GstCaps *videoCaps;

    // GstBus *bus;

    videosrc = gst_element_factory_make("v4l2src", "videosrc");
    g_object_set(videosrc,"device", glb::constants::VIDEO_SRC_PATH.c_str(),
                 "io-mode", 4, "do-timestamp", TRUE, NULL);

    sink = gst_element_factory_make("filesink", "sink");
    g_object_set(sink, "location", glb::constants::OUT_PATH.c_str(), NULL);

    videoCaps = gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB",
            "framerate", GST_TYPE_FRACTION, 60, 1,
            "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
            "width", G_TYPE_INT, glb::constants::WIDTH,
            "height", G_TYPE_INT, glb::constants::HEIGHT,
            NULL);

    capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    g_object_set(capsfilter, "caps", videoCaps, NULL);

    gst_caps_unref(videoCaps);

    pipeline = gst_pipeline_new("pipeline");

    // bus = gst_element_get_bus(pipeline);

    gst_bin_add_many(GST_BIN(pipeline), videosrc, capsfilter, sink, NULL);
    gst_element_link_many(videosrc, capsfilter, sink, NULL);

    std::thread appsrcPushBufferThread = std::thread([&](){
        std::this_thread::sleep_for (std::chrono::seconds(2));

        gst_element_change_state(pipeline, GST_STATE_CHANGE_PLAYING_TO_PAUSED);
        gst_element_change_state(pipeline, GST_STATE_CHANGE_PAUSED_TO_READY);
        gst_element_set_state (pipeline, GST_STATE_NULL);
    });

    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    // TODO Clean resources

    return a.exec();
}
