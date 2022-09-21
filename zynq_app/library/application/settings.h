#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

//! \brief Singleton used to store settings
//! \note It might be replaced and done better way
struct Settings
{
public:
    static Settings& getInstance();

    struct
    {
        std::string ip_address{"10.15.1.77"};
        int port = 9002;
    } rtp;

    struct
    {
        // ...
    } display;

    struct
    {
        std::string videoSrc {"/dev/video0"};
        std::string videoOut {"/video-res"};
        std::string cameraUart {"/dev/ttyUSB0"};
    } path;

    struct
    {
        // ...
    } file;

private:
    Settings() = default;

};

#endif // SETTINGS_H
