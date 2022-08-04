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

    struct Power {
        static const byteArray<5> On() { return {0x01, 0x04, 0x00, 0x02, 0xFF}; };
        static const byteArray<5> Off() { return {0x01, 0x04, 0x00, 0x03, 0xFF}; };
    };

    struct Exposure {
        enum Mode {FULL_AUTO = 0x00, MANUAL = 0x03, SHUTTER_PRI = 0x0A, IRIS_PRI = 0x0B, GAIN_PRI = 0x0E };
        static const byteArray<5> SetMode(Mode mode) { return {0x01, 0x04, 0x39, (uint8_t) mode, 0xFF}; };

        struct Gain {

            // TODO made into enum
            static const byteArray<5> Reset() { return { 0x01, 0x04, 0x0C, 0x00, 0xFF}; };
            static const byteArray<5> Up() { return { 0x01, 0x04, 0x0C, 0x02, 0xFF}; };
            static const byteArray<5> Down() { return { 0x01, 0x04, 0x0C, 0x03, 0xFF}; };

            static const byteArray<8> Direct(uint8_t gain) { return { 0x01, 0x04, 0x4C, 0x00, 0x00, (uint8_t) ((gain >> 4) & 0x0F), (uint8_t) (gain & 0x0F), 0xFF}; };

            // limit          - 8x 01 04 2C 0p FF    - p: 4 (9dB) - 9 (24dB), F (Off)
            // point          - 8x 01 05 0C 0p FF    - p: 2=On, 3=Off
            // point position - 8x 01 05 4C 0p 0p FF - pp: 01 (0dB) - 09 (24dB)
        };

        struct Irirs {
            // Reset        - 8x 01 04 0B 00 FF          - To return to F2.8 value
            // Up (Open)    - 8x 01 04 0B 02 FF
            // Down (Close) - 8x 01 04 0B 03 FF
            // Direct       - 8x 01 04 4B 00 00 0p 0p FF - pp: Iris Position 05 - 15
        };

        struct Shutter {
            // Reset  - 8x 01 04 0A 00 FF
            // Up     - 8x 01 04 0A 02 FF
            // Down   - 8x 01 04 0A 03 FF
            // Direct - 8x 01 04 4A 00 00 0p 0p FF - pp: Shutter Position (01 - 15)

            // Max    - 8x 01 05 2A 00 0p 0p FF    - pp: 03 - 15
            // Min    - 8x 01 05 2A 01 0p 0p FF    - pp: 03 - 15
        };

        // AE Speed, Exp Comp, Back Light, spot light, visibility enhancer, ir cut, low light basis brightness, nd filter, ...
    };

    namespace Color {
        struct WhiteBalance{
            enum Mode {AUTO = 0, INDOOR = 1, OUTDOOR = 2, ONE_PUSH = 3, MANUAL = 5, OUTDOOR_AUTO = 6, SODIUM_LAMP_AUTO = 7, SODIUM_AUTO = 8 };
            static const byteArray<5> SetMode(Mode mode) { return {0x01, 0x04, 0x35, (uint8_t) mode, 0xFF}; };

            // One Push Trigger - 8x 01 04 10 05 FF
        };

        struct RGain {
            // Reset  - 8x 01 04 03 00 FF          - To return to 80 (0) value
            // Up     - 8x 01 04 03 02 FF
            // Down   - 8x 01 04 03 03 FF
            // Direct - 8x 01 04 43 00 00 0p 0p FF - pp: 00 (–128) - 80 (0) - FF (128)
        };

        struct BGain {
            // Reset  - 8x 01 04 04 00 FF          - To return to 80 (0) value
            // Up     - 8x 01 04 04 02 FF
            // Down   - 8x 01 04 04 03 FF
            // Direct - 8x 01 04 44 00 00 0p 0p FF - pp: 00 (–128) - 80 (0) - FF (128)
        };

        // Spped - 8x 01 04 56 0p FF p: speed 1 (Slow) - 5 (Fast)

        struct Offset {
            // Reset  - 8x 01 7E 01 2E 00 00 FF - To return to 7 (0) value
            // Up     - 8x 01 7E 01 2E 00 02 FF
            // Down   - 8x 01 7E 01 2E 00 03 FF
            // Direct - 8x 01 7E 01 2E 01 0p FF - p: 0 (–7) - 7 (0) - E (+7)
        };

        // Chroma suppress, matrix, level, phase, R-G, R-B, ..., B-G
    };

    namespace Detail {
        struct Level {
            // Reset  - 8x 01 04 02 00 FF          - To return to 7 (0) value
            // Up     - 8x 01 04 02 02 FF
            // Down   - 8x 01 04 02 03 FF
            // Direct - 8x 01 04 42 00 00 0p 0p FF - pp: Aperture Gain 00 - 0F
        };

        // Mode, bandwith, crispening, h/v balance, b/w balance, limit, highlightide tail, superlow
    }

    struct Knee {
        // On/Off       - 8x 01 7E 01 6D 0p FF    - p: 2=On, 3=Off
        // Mode         - 8x 01 7E 01 54 0p FF    - p: 0=Auto, 4=Manual
        // Slope Direct - 8x 01 7E 01 6F 0p 0p FF - pp: Knee Slope 00 - 0E
        // Point Direct - 8x 01 7E 01 6E 0p 0p FF - pp: Knee Point 00 - 0C
    };

    struct Gamma{
        enum Mode {STD = 0, STRAIGHT = 1, PATTERN = 2, MOVIE = 8, STILL = 9, CINE1 = 0xA, CINE2  = 0xB, CINE3 = 0xC, CINE4  = 0xE, ITU709  = 0xE};
        static const byteArray<5> SetMode(Mode mode) { return {0x01, 0x04, 0x5B, (uint8_t) (mode), 0xFF}; };

        // Pattern           - 8x 01 05 5B 0p 0p 0p FF          - ppp: 001 - 200
        // Offset            - 8x 01 04 1E 00 00 00 0p 0q 0q FF - p: Offset polarity 0 (+), 1 (–) and qq: Offset width 00 - 40
        // Level             - 8x 01 7E 01 71 0p 0p FF          - pp: 00 - 0E
        // Black gamma level - 8x 01 7E 01 72 0p 0p FF          - pp: 00 - 0E
        // Black gamma range - 8x 01 05 5C 0p FF                - p: Correction range 0 (Low), 1 (Mid), 2 (High)

        struct BlackLevel {
            // Reset  - 8x 01 7E 04 15 00 FF    - To return to 30 (0) value
            // Up     - 8x 01 7E 04 15 02 FF
            // Down   - 8x 01 7E 04 15 03 FF
            // Direct - 8x 01 7E 04 45 0p 0p FF - pp: 00 (–48) - 60 (48)
        };
    };

    // Picture profile mode   - 8x 01 7E 04 5F 0p FF p: - Picture profile setting (0=PP1, 1=PP2, 2=PP3, 3=PP4, 4=PP5, 5=PP6)
    // Flicker reduction mode - 8x 01 04 32 0p FF       - p:2=On, 3=Off
    // Noise reduction mode   -  8x 01 04 53 pp FF      - pp: NR Setting 00 (Off), 01 (Weak) - 05 (Strong), 7F (Advanced)
    // Noise reduction 2D NR/3D NR - ...

    struct Zoom {
        static byteArray<5> TeleStandard() { return {0x01, 0x04, 0x07, 0x02,  0xFF}; };
        static byteArray<5> WideStandard() { return {0x01, 0x04, 0x07, 0x03,  0xFF}; };
        static byteArray<5> TeleVariable(uint8_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x20|(speed > 7? 7 : speed)),  0xFF}; };
        static byteArray<5> WideVariable(uint8_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x30|(speed > 7? 7 : speed)),  0xFF}; };
        static byteArray<5> Direct(uint32_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x30|(speed > 7? 7 : speed)),  0xFF}; };

        // Clear image zoom - 8x 01 04 06 03 FF    - OFF
        //                  - 8x 01 04 06 04 FF    - ON

        // Teleconvert mode - 8x 01 7E 04 36 0p FF - p: 2=Double, 3=Off*1
    };

    struct Focus {
        // ...
    };

    struct PanTilt {
        // ...
    };

    struct Preset {
        // ...
    };

    struct Hdmi {
        enum Format { _1920_1080_59_94 = 0x00, _1920_1080_29_97 = 0x02, /* ... */ };
        enum Colorspace {YCBCR = 0, RGB = 1};

        // SetFormat     - 8x 01 7E 01 1E 0p 0p FF
        // SetColorspace - 8x 01 7E 01 03 00 0p FF
    };
}

#endif // VISCACOMMANDS_H
