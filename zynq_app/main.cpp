#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>

#include <graphic/menu/menubuilder.h>

#include "library/visible/gstreamer/gsfacade.h"
#include "library/visible/visca/visca.h"
#include "global/config.h"
#include "graphic/mainWindow.h"

void nonEssentialSetup()
{
    qSetMessagePattern("(%{category}) %{function} - %{message}");
}

// TODO Temp for Wiris...
class Visible
{
public:
    Visible()
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
        streamData.sink = gst_element_factory_make("udpsink", "sink");

        // Host address and port for streaming
        g_object_set(streamData.sink, "port", 9002, NULL);
        g_object_set(streamData.sink, "host", "10.15.1.77", NULL);

        // $ gst-launch-1.0 udpsrc port="9002" caps="application/x-rtp, media=(string)video, encoding-name=H264, payload=96" ! rtph264depay ! avdec_h264  ! autovideosink

        g_object_set (streamData.source, "device", "/dev/video0", NULL);

        g_object_set (streamData.enc, "idr-interval", 5, NULL);
        g_object_set (streamData.enc, "bitrate", 4096, NULL);

        streamData.pipeline = gst_pipeline_new ("pipeline_sink");

        GstCaps *caps = gst_caps_new_any();

        streamData.capsfilter = gst_element_factory_make("capsfilter", "caps");
        g_object_set(streamData.capsfilter, "caps", caps, NULL);
        gst_caps_unref(caps);

        gst_bin_add_many (GST_BIN (streamData.pipeline), streamData.source, streamData.queue, streamData.transform,
                          streamData.enc, streamData.parse, streamData.rtph264pay, streamData.sink, NULL);

        if (gst_element_link_many(streamData.source, streamData.transform, streamData.enc, streamData.parse, streamData.rtph264pay, streamData.sink, NULL) != TRUE)
        {
            gst_object_unref (streamData.pipeline);
            throw std::runtime_error("Elements could not be linked.");
        }

        gst_element_set_state (streamData.pipeline, GST_STATE_PLAYING);        
    }

private:
    struct {
        GstElement *pipeline, *source, *queue, *capsfilter, *transform, *enc, *parse, *rtph264pay, *sink;
        GstCaps *caps = nullptr;
    } streamData;
};

int main(int argc, char *argv[])
{
    nonEssentialSetup();

    QApplication a(argc, argv);

    Visible visible;

    // Setup gstreamer pipelines from cam
    // GsFacade gsFacade{};
    // gsFacade.initAndStart(GsFacade::RAW_RTP | GsFacade::RAW_DISPLAY);

    // Setup Visca protocol
    Visca visca(glb::path::CAMERA_UART.c_str());

    // Create UI
    Menu &menu = Menu::getInstance();

    Controller controller(visca);
    MenuBuilder::buildMenuTree(menu.m_root.get(), static_cast<QWidget*>(&menu), &controller);

    menu.show();

    return a.exec();
}
