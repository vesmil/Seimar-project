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
}

#endif
