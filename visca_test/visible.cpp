#include "visible.h"

#include <stdexcept>
#include <fstream>

bool Visible::isMxcVideo(const std::string &name)
{
    std::ifstream file("/sys/class/video4linux/" + name + "/name");

    if (!file)
        return false;

    std::string camera;
    file >> camera;
    return camera == "Mxc";
}

// Ugly temp pipeline for testing effects of VISCA commands
Visible::Visible()
{
    gst_init(nullptr, nullptr);
    gst_debug_set_active(TRUE);
    gst_debug_set_default_threshold(GST_LEVEL_FIXME);

    streamData.source = gst_element_factory_make("imxv4l2videosrc", "source");
    streamData.queue = gst_element_factory_make("queue", "queue");
    streamData.transform = gst_element_factory_make("imxipuvideotransform", "transform");
    streamData.enc = gst_element_factory_make("imxvpuenc_h264", "encode");
    streamData.parse = gst_element_factory_make("h264parse", "parse");
    streamData.rtph264pay = gst_element_factory_make("rtph264pay", "rtph264pay");
    streamData.udpsink = gst_element_factory_make("udpsink", "sink");

    // Host address and port for streaming
    g_object_set(streamData.udpsink, "port", 9002, NULL);
    g_object_set(streamData.udpsink, "host", "10.15.1.77", NULL);

    // $ gst-launch-1.0 udpsrc port="9002" caps="application/x-rtp, media=(string)video, encoding-name=H264, payload=96" ! rtph264depay ! avdec_h264  ! autovideosink

    if (isMxcVideo("video0")) {
        g_object_set (streamData.source, "device", "/dev/video0", NULL);
    } else if (isMxcVideo("video1")) {
        g_object_set (streamData.source, "device", "/dev/video1", NULL);
    } else {
        throw std::runtime_error("Camera not connected");
    }

    g_object_set (streamData.enc, "idr-interval", 5, NULL);
    g_object_set (streamData.enc, "bitrate", 4096, NULL);

    streamData.pipeline = gst_pipeline_new ("pipeline_sink");

    GstCaps *caps = gst_caps_new_any();

    streamData.capsfilter = gst_element_factory_make("capsfilter", "caps");
    g_object_set(streamData.capsfilter, "caps", caps, NULL);
    gst_caps_unref(caps);

    gst_bin_add_many (GST_BIN (streamData.pipeline), streamData.source, streamData.queue, streamData.transform, streamData.enc, streamData.parse, streamData.rtph264pay, streamData.udpsink, NULL);

    if (gst_element_link_many(streamData.source, streamData.transform, streamData.enc, streamData.parse, streamData.rtph264pay, streamData.udpsink, NULL) != TRUE) {
        gst_object_unref (streamData.pipeline);
        throw std::runtime_error("Elements could not be linked.\n");
    }

    gst_element_set_state (streamData.pipeline, GST_STATE_PLAYING);
}
