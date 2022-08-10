#ifndef GLB_CONFIG_H
#define GLB_CONFIG_H

#include <string>
#include <gst/gst.h>

namespace glb
{
    namespace path
    {
        static const std::string VIDEO_SRC {"/dev/video0"};
        static const std::string VIDEO_OUT {"/video-res"};
    }

    namespace rtp
    {
        static const std::string IP_ADDRESS("10.15.1.77");
        static const int PORT = 9002;
    }
}

#endif
