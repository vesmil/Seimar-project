#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

struct Settings
{
public:
    static Settings& getInstance();

    struct
    {
        std::string ip_address{"10.15.1.77"};
        int port = 9002;
    } rtp;

    struct Visca
    {
        // ...
    };

    struct Display
    {
        // ...
    };

    struct File
    {
        // ...
    };

private:
    Settings();

};

#endif // SETTINGS_H
