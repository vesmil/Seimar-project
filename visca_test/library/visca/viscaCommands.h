#ifndef VISCACOMMANDS_H
#define VISCACOMMANDS_H

#include <array>
#include <stdint.h>
#include <string>

// Duplicates could probably be avoided using builder pattern
//   ...but it would unnecessarily increase the complexity and would be slower

struct ViscaCommands
{
    template <std::size_t size>
    using byteArray = std::array<uint8_t, size>;

    enum CommandType : uint8_t { CONTROL = 0x01, INQUIRY = 0x09 };
    enum ChangeEnum  : uint8_t { RESET = 0x00, UP = 0x02, DOWN = 0x03 };
    enum State       : uint8_t { ON = 0x02, OFF = 0x03 };

    struct Init
    {
        static const byteArray<3> AddressSet() { return { 0x30, 0x01, 0xFF}; };
        static const byteArray<4> IfClear()    { return { CONTROL, 0x00, 0x01, 0xFF}; };
    };

    struct Power
    {
        static const byteArray<5> SetState(State state) { return {CONTROL, 0x04, 0x00, state, 0xFF}; };

        static const byteArray<5> GetState()            { return {INQUIRY, 0x04, 0x00, 0xFF}; };
        static State StateFromReply(byteArray<4> reply) { return (State) reply[2];} ;
    };

    struct Exposure
    {
        enum Mode : uint8_t {FULL_AUTO = 0x00, MANUAL = 0x03, SHUTTER_PRI = 0x0A, IRIS_PRI = 0x0B, GAIN_PRI = 0x0E };

        static const byteArray<5> SetMode(Mode mode)  { return { CONTROL, 0x04, 0x39, mode, 0xFF}; };

        static const byteArray<5> GetMode()           { return { INQUIRY, 0x04, 0x39, 0xFF}; };
        static Mode ModeFromReply(byteArray<4> reply) { return (Mode) reply[2];} ;

        struct Irirs
        {
            static const byteArray<5> Change(ChangeEnum change) { return { CONTROL, 0x04, 0x0B, change, 0xFF}; };

            //! \brief returns command packet for setting iris - value is in range 05 - 15
            static const byteArray<8> SetValue(uint8_t value) { return { CONTROL, 0x04, 0x4B, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; };

            static const byteArray<5> GetValue()              { return { INQUIRY, 0x04, 0x4B, 0xFF}; };
            static uint8_t ValueFromReply(byteArray<4> reply) { return ( reply[4] << 4) + reply[5]; };  // TODO parsing into a function
        };

        struct Gain
        {
            static const byteArray<5> Change(ChangeEnum change) { return { CONTROL, 0x04, 0x0C, change, 0xFF}; };

            //! \brief returns command packet for setting gain - value is in range 00 (–3dB) - 0C (33 dB)
            static const byteArray<8> Direct(uint8_t value) { return { CONTROL, 0x04, 0x4C, 0x00, 0x00, 0, ensureMaxU8(value, 0x0C), 0xFF}; };

            //! \brief returns command packet for setting gain limit - value is in range 4 (9dB) - 9 (24dB)
            static const byteArray<5> Limit(uint8_t value) { return { CONTROL, 0x04, 0x2C, ensureConstratitsU8(value, 4, 9), 0xFF}; };
            static const byteArray<5> LimitOff()           { return { CONTROL, 0x04, 0x2C, 0x0F, 0xFF}; };

            //! \brief returns command packet for setting gain point
            static const byteArray<5> Point(State state) { return { CONTROL, 0x05, 0x0C, state, 0xFF}; };

            //! \brief returns command packet for setting gain point position - value is in range 01 (0dB) - 09 (24dB)
            static const byteArray<6> PointPosition(uint8_t value) { return { CONTROL, 0x05, 0x4C, 0x00, ensureMaxU8(value, 0x09), 0xFF}; };
        };

        struct Shutter
        {
            static const byteArray<5> Change(ChangeEnum change) { return { CONTROL, 0x04, 0x0A, change, 0xFF}; };

            //! \brief returns command packet for setting shutter - value is in range 0x01 - 0x15
            static const byteArray<8> Set(uint8_t value) { return { CONTROL, 0x04, 0x4A, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; };
            static const byteArray<4> Get()              { return { INQUIRY, 0x04, 0x4A, 0xFF}; };
            // TODO shutter from reply...
        };

        // Max/min shutter, AE Speed, Exp Comp, Back Light, spot light, visibility enhancer, ir cut, low light basis brightness, nd filter
    };

    struct Color
    {
        static const byteArray<5> Speed(uint8_t value) { return {CONTROL, 0x04, 0x56, ensureConstratitsU8(value, 0x01, 0x59), 0xFF}; };

        struct WhiteBalance
        {
            enum Mode : uint8_t {AUTO = 0, INDOOR = 1, OUTDOOR = 2, ONE_PUSH = 3, MANUAL = 5, OUTDOOR_AUTO = 6, SODIUM_LAMP_AUTO = 7, SODIUM_AUTO = 8 };

            static const byteArray<5> SetMode(Mode mode) { return {0x01, 0x04, 0x35, mode, 0xFF}; };
        };

        struct RGain
        {
            static const byteArray<7> Change(ChangeEnum change) { return { CONTROL, 0x04, 0x03, change, 0xFF}; };

            // Direct - 8x 01 04 43 00 00 0p 0p FF - pp: 00 (–128) - 80 (0) - FF (128)
        };

        struct BGain
        {
            static const byteArray<7> Change(ChangeEnum change) { return { CONTROL, 0x04, 0x04, change, 0xFF}; };

            // Direct - 8x 01 04 44 00 00 0p 0p FF - pp: 00 (–128) - 80 (0) - FF (128)
        };

        struct Offset
        {
            static const byteArray<7> Change(ChangeEnum change) { return { CONTROL, 0x7E, 0x01, 0x2E, 0x00, change, 0xFF}; };

            // Direct - 8x 01 7E 01 2E 01 0p FF - p: 0 (–7) - 7 (0) - E (+7)
        };

        // Chroma suppress, matrix, level, phase, R-G, R-B, ..., B-G
    };

    struct Detail
    {
        struct Level
        {
            static const byteArray<5> Change(ChangeEnum change) { return { CONTROL, 0x04, 0x02, change, 0xFF}; };

            // Direct - 8x 01 04 42 00 00 0p 0p FF - pp: Aperture Gain 00 - 0F
        };

        // Mode, bandwith, crispening, h/v balance, b/w balance, limit, highlightide tail, superlow
    };

    struct Knee
    {
        static const byteArray<6> SetState(State state) { return {CONTROL, 0x7E, 0x01, 0x6D, state, 0xFF}; };

        // Mode         - 8x 01 7E 01 54 0p FF    - p: 0=Auto, 4=Manual
        // Slope Direct - 8x 01 7E 01 6F 0p 0p FF - pp: Knee Slope 00 - 0E
        // Point Direct - 8x 01 7E 01 6E 0p 0p FF - pp: Knee Point 00 - 0C
    };

    struct Gamma
    {
        enum Mode : uint8_t {STD = 0, STRAIGHT = 1, PATTERN = 2, MOVIE = 8, STILL = 9, CINE1 = 0xA, CINE2  = 0xB, CINE3 = 0xC, CINE4  = 0xE, ITU709  = 0xE};
        static const byteArray<5> SetMode(Mode mode) { return {0x01, 0x04, 0x5B, mode, 0xFF}; };

        // Pattern           - 8x 01 05 5B 0p 0p 0p FF          - ppp: 001 - 200
        // Offset            - 8x 01 04 1E 00 00 00 0p 0q 0q FF - p: Offset polarity 0 (+), 1 (–) and qq: Offset width 00 - 40

        static const byteArray<7> Level(uint8_t value) { return { CONTROL, 0x7E, 0x01, 0x71, 00, ensureMaxU8(value, 0x0E), 0xFF}; };

        // Black gamma level - 8x 01 7E 01 72 0p 0p FF          - pp: 00 - 0E
        // Black gamma range - 8x 01 05 5C 0p FF                - p: Correction range 0 (Low), 1 (Mid), 2 (High)

        struct BlackLevel
        {
            // Reset  - 8x 01 7E 04 15 00 FF    - To return to 30 (0) value
            // Up     - 8x 01 7E 04 15 02 FF
            // Down   - 8x 01 7E 04 15 03 FF
            // Direct - 8x 01 7E 04 45 0p 0p FF - pp:

            //! \brief returns command packet for chaning gamma black level - value is in range 0x00 (–48) - 0x60 (48)
            static byteArray<8> Direct(uint16_t value)
            {
                uint16_t limitedValue = ensureMaxU16(value, 0x4000);
                return {0x01, 0x04, 0x47, parseParam(limitedValue, 3), parseParam(limitedValue, 2), parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
            };

        };
    };

    // Picture profile mode   - 8x 01 7E 04 5F 0p FF p: - Picture profile setting (0=PP1, 1=PP2, 2=PP3, 3=PP4, 4=PP5, 5=PP6)
    // Flicker reduction mode - 8x 01 04 32 0p FF       - p:2=On, 3=Off

    //! \brief returns command packet for changing noise reduction - value is in range 01 (Weak) - 05 (Strong)
    static const byteArray<5> FlickerReduction(State state) { return {CONTROL, 0x04, 0x32, state, 0xFF}; };

    //! \brief returns command packet for changing noise reduction - value is in range 01 (Weak) - 05 (Strong)
    static const byteArray<5> NoiseReduction(uint8_t value) { return {CONTROL, 0x04, 0x53, ensureMaxU8(value, 05), 0xFF}; }; // Missing 7F Advanced

    // Noise reduction 2D NR/3D NR - ...

    struct Zoom
    {
        static byteArray<5> Stop()         { return {0x01, 0x04, 0x07, 0x00,  0xFF}; };
        static byteArray<5> TeleStandard() { return {0x01, 0x04, 0x07, 0x02,  0xFF}; };
        static byteArray<5> WideStandard() { return {0x01, 0x04, 0x07, 0x03,  0xFF}; };

        //! \brief speed is in range 0 - 7 (from slowest to fastest)
        static byteArray<5> TeleVariable(uint8_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x20|(ensureMaxU8(speed, 7U))),  0xFF}; };
        //! \brief speed is in range 0 - 7 (from slowest to fastest)
        static byteArray<5> WideVariable(uint8_t speed) { return {0x01, 0x04, 0x07, (uint8_t) (0x30|(ensureMaxU8(speed, 7U))),  0xFF}; };

        //! \brief value is in range 0x0 - 0x4000 (from wide to tele)
        static byteArray<8> Direct(uint16_t value)
        {
            uint16_t limitedValue = ensureMaxU16(value, 0x4000);
            return {0x01, 0x04, 0x47, parseParam(limitedValue, 3), parseParam(limitedValue, 2), parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
        };

        // Clear image zoom - 8x 01 04 06 03 FF    - OFF
        //                  - 8x 01 04 06 04 FF    - ON

        // Teleconvert mode - 8x 01 7E 04 36 0p FF - p: 2=Double, 3=Off*1
    };

    struct Focus
    {
        static const byteArray<5> AutoFocus(State state) { return {CONTROL, 0x04, 0x38, state, 0xFF}; };

        // Near ...
        // Far ...
        // Inf ...
        // Direct ...
    };

    struct PanTilt
    {
        // ...
    };

    struct Preset
    {
        // ...
    };

    struct Hdmi
    {
        enum Format : uint8_t { _1920_1080_59_94 = 0x00, _1920_1080_29_97 = 0x02, /* TODO ... */ };
        enum Colorspace : uint8_t {YCBCR = 0, RGB = 1};

        static const byteArray<7> SetFormat(Format format)             { return {0x01, 0x7E, 0x01, 0x1E, parseParam(format, 1), parseParam(format, 0), 0xFF}; };
        static const byteArray<7> SetcolorSpace(Colorspace colorSpace) { return {0x01, 0x7E, 0x01, 0x03, 0x00, colorSpace, 0xFF}; };
    };

private:
    // TODO - should be added notification for limit violation?

    //! \brief returns value if value is less than max, else returns max (for uint8_t)
    static uint8_t ensureMaxU8(uint8_t value, uint8_t max) { return value > max? max : value; }

    //! \brief returns value if within limits or return the limit
    static uint8_t ensureConstratitsU8(uint8_t value, uint8_t min, uint8_t max) { return value > max? max : (value < min? min : value); }

    //! \brief returns value if value is less than max, else returns max (for uint16_t)
    static uint16_t ensureMaxU16(uint16_t value, uint16_t max) { return value > max? max : value; }

    //! \brief used to split many bytes to half bytes - return least significant 4 bits from RShifting value by 4 * ordinal
    //! \example parseParam(0x1234, 1) will return 2
    static uint8_t parseParam(uint16_t value, uint8_t reversedOrdinal) { return (value >> reversedOrdinal * 4) & 0x0F; }
};

#endif // VISCACOMMANDS_H
