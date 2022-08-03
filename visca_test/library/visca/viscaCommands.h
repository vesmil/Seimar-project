#ifndef VISCACOMMANDS_H
#define VISCACOMMANDS_H

#include <stdint.h>
#include <string>

namespace ViscaCommands {
    namespace Init {
        static uint8_t ADDRESS_SET[] = {0x88, 0x30, 0x01,  0xFF};
        static uint8_t IF_CLEAR[] = {0x81, 0x01, 0x00, 0x01, 0xFF};
    };

    namespace Exposure {
        namespace Mode {
            static uint8_t FULL_AUTO[] = {0x80, 0x01, 0x04, 0x39, 0x00, 0xFF};
            // constexpr static uint8_t MANUAL[] = {TAddress, 0x01, 0x04, 0x39, 0x03, 0xFF};
            // ...
        };

        struct Gain {
            // constexpr static uint8_t UP[] = {TAddress, 0x01, 0x04, 0x0C, 0x02, 0xFF};
            // constexpr static uint8_t DOWN[] = {TAddress, 0x01, 0x04, 0x0C, 0x03, 0xFF};
        };

        // ...
    };

    struct Color {

    };

}

#endif // VISCACOMMANDS_H
