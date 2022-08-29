#ifndef GLB_CONFIG_H
#define GLB_CONFIG_H

#include <QString>
#include <string>
#include <gst/gst.h>

namespace glb
{
    namespace path
    {
        static const std::string VIDEO_SRC {"/dev/video0"};
        static const std::string VIDEO_OUT {"/video-res"};

        static const std::string CAMERA_UART {"/dev/ttymxc4"};
    }

    namespace rtp
    {
        static const std::string IP_ADDRESS("10.15.1.77");
        static const int PORT = 9002;
    }

    namespace path
    {
        static const QString APP = "/opt/wiris-pro/";
        static const QString IMG = APP + "image/";
        static const QString LANG = APP + "language/";
        static const QString FONT = APP + "font/";
        static const QString SET = APP + "settings.txt";
        static const QString SYS = "/opt/system/";
        static const QString FILE_WWE = SYS + "wwe";
    }
}

#endif
