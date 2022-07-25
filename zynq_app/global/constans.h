#ifndef GLB_CONSTANS_H
#define GLB_CONSTANS_H

#include <string>
#include <gst/gst.h>

namespace glb
{
    namespace path
    {
        const std::string VIDEO_SRC {"/dev/video0"};
        const std::string VIDEO_OUT {"/media/sd-mmcblk0p2/video-res"};
    }

    namespace rtp
    {
        const std::string IP_ADDRESS("10.15.1.77");
        const int PORT = 9002;
    }

    namespace dim
    {
        const int WIDTH = 1024;
        const int HEIGHT = 768;
    }
}

#endif
