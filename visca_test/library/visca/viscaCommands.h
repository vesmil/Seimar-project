#ifndef VISCACOMMANDS_H
#define VISCACOMMANDS_H

#include <array>
#include <stdint.h>
#include <string>

namespace ViscaCommands {

    template <std::size_t size>
    using byteArray = std::array<uint8_t, size>;

    struct Init {
        static const byteArray<3> AddressSet() { return {0x30, 0x01,  0xFF}; };
        static const byteArray<4> IfClear() { return {0x01, 0x00, 0x01, 0xFF}; };
    };

    namespace Exposure {
        struct Mode {
            static const byteArray<5> FullAuto() { return {0x01, 0x04, 0x39, 0x00, 0xFF}; };
            static const byteArray<5> Manual() { return {0x01, 0x04, 0x39, 0x03, 0xFF}; };
            static const byteArray<5> Bright() { return {0x01, 0x04, 0x39, 0x0D, 0xFF}; };
        };

        struct Gain {
            static const byteArray<5> Reset() { return { 0x01, 0x04, 0x0C, 0x00, 0xFF}; };
            static const byteArray<5> Up() { return { 0x01, 0x04, 0x0C, 0x02, 0xFF}; };
            static const byteArray<5> Down() { return { 0x01, 0x04, 0x0C, 0x03, 0xFF}; };
            static const byteArray<8> Direct(uint8_t gain) { return { 0x01, 0x04, 0x4C, 00, 00, gain, gain, 0xFF}; }; // TODO
        };
    };

    namespace Color {
        struct WhiteBalance{
            // ...
        };
    };

    namespace Detail {
        struct Level {
            // ...
        };
    }

    struct Gamma{
        enum MODE {STD = 0, STRAIGHT = 1, PATTERN = 2, MOVIE = 8, STILL = 9, CINE1 = 0xA, CINE2  = 0xB, CINE3 = 0xC, CINE4  = 0xE, ITU709  = 0xE};
        static const byteArray<5> SetMode(MODE mode) { return {0x01, 0x04, 0x5B, (uint8_t) (0x00 | mode), 0xFF}; };

        // ...
    };

    struct Zoom {
        static byteArray<5> TeleStandard() { return {0x01, 0x04, 0x07, 0x02,  0xFF}; };
        static byteArray<5> WideStandard() { return {0x01, 0x04, 0x07, 0x03,  0xFF}; };
        static byteArray<5> TeleVariable(uint8_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x20|(speed > 7? 7 : speed)),  0xFF}; };
        static byteArray<5> WideVariable(uint8_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x30|(speed > 7? 7 : speed)),  0xFF}; };
    };
}

#endif // VISCACOMMANDS_H
