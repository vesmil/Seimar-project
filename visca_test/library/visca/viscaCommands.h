#ifndef VISCACOMMANDS_H
#define VISCACOMMANDS_H

#include <array>
#include <stdint.h>
#include <string>

#include "global/logCategories.h"

// Duplicates could probably be avoided using builder pattern
//  ...but it would unnecessarily increase the complexity and would be slower

namespace {
    // TODO - should be added notification for limit violation?

    //! \brief returns value if value is less than max, else returns max (for uint8_t)
    static constexpr uint8_t ensureMaxU8(uint8_t value, uint8_t max) { return value > max? max : value; }

    //! \brief returns value if within limits or return the limit
    static constexpr uint8_t ensureconstexprratitsU8(uint8_t value, uint8_t min, uint8_t max) { return value > max? max : (value < min? min : value); }

    //! \brief returns value if value is less than max, else returns max (for uint16_t)
    static constexpr uint16_t ensureMaxU16(uint16_t value, uint16_t max) { return value > max? max : value; }

    //! \brief used to split many bytes to half bytes - return least significant 4 bits from RShifting value by 4 * ordinal
    //! \example parseParam(0x1234, 1) will return 2
    static constexpr uint8_t parseParam(uint16_t value, uint8_t reversedOrdinal) { return (value >> reversedOrdinal * 4) & 0x0F; }

    //! \brief Reverse of parseParam - combines multiple halfbytes into one numbers
    template <typename T, typename... Ts>
    static constexpr T reversePrase(T firstParam, Ts ... params)
    {
        T total = firstParam;

        for(const auto p : {params...}) {
            total = total << 4;
            total += p;
        }

        return total;
    }
}

namespace ViscaCommands
{    
    template <std::size_t size>
    using byteArray = std::array<uint8_t, size>;

    enum CommandType : uint8_t { CTRL = 0x01, INQ = 0x09 };
    enum ChangeEnum  : uint8_t { RESET = 0x00, UP = 0x02, DOWN = 0x03 };
    enum State       : uint8_t { ON = 0x02, OFF = 0x03 };

    namespace Init
    {
        static constexpr byteArray<3> addressSet() { return { 0x30, 0x01, 0xFF}; };
        static constexpr byteArray<4> ifClear()    { return { CTRL, 0x00, 0x01, 0xFF}; };

        static constexpr byteArray<4> getVersionInfo() { return { INQ, 0x00, 0x02, 0xFF}; };
        static void printVersionInfo(byteArray<10> reply)
        {
            qCInfo(viscaLog()) << "Vender ID:" << hex << (((uint16_t) reply[2] << 8) + reply[3]);
            qCInfo(viscaLog()) << "Model ID:" << hex << (((uint16_t) reply[4] << 8) + reply[5]);
            qCInfo(viscaLog()) << "ROM revison:" << hex << (((uint16_t) reply[6] << 8) + reply[7]);
            qCInfo(viscaLog()) << "Maximum socket #:" << hex << (reply[8]);
        };
    };

    namespace Power
    {
        static constexpr byteArray<5> setState(State state) { return {CTRL, 0x04, 0x00, state, 0xFF}; };
        static constexpr byteArray<5> getState()            { return {INQ, 0x04, 0x00, 0xFF}; };
        static State stateFromReply(byteArray<4> reply) { return (State) reply[2];} ;
    };

    namespace Exposure
    {
        enum Mode : uint8_t {FULL_AUTO = 0x00, MANUAL = 0x03, SHUTTER_PRI = 0x0A, IRIS_PRI = 0x0B, GAIN_PRI = 0x0E };

        static constexpr byteArray<5> setMode(Mode mode)  { return { CTRL, 0x04, 0x39, mode, 0xFF}; };

        static constexpr byteArray<5> getMode()           { return { INQ, 0x04, 0x39, 0xFF}; };
        static Mode modeFromReply(byteArray<4> reply) { return (Mode) reply[2];} ;

        namespace Irirs
        {
            static constexpr byteArray<5> change(ChangeEnum change) { return { CTRL, 0x04, 0x0B, change, 0xFF}; };

            //! \brief returns command packet for setting iris - value is in range 05 - 15
            static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x4B, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; };

            static constexpr byteArray<5> getValue()              { return { INQ, 0x04, 0x4B, 0xFF}; };
            static uint8_t valueFromReply(byteArray<7> reply) { return reversePrase(reply[4], reply[5]); };
        };

        namespace Gain
        {
            static constexpr byteArray<5> change(ChangeEnum change) { return { CTRL, 0x04, 0x0C, change, 0xFF}; };

            //! \brief returns command packet for setting gain - value is in range 00 (–3dB) - 0C (33 dB)
            static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x4C, 0x00, 0x00, 0, ensureMaxU8(value, 0x0C), 0xFF}; };
            static constexpr byteArray<5> getValue()              { return { INQ, 0x04, 0x4C, 0xFF}; };
            static uint8_t valueFromReply(byteArray<7> reply) { return reversePrase(reply[4], reply[5]); };

            //! \brief returns command packet for setting gain limit - value is in range 4 (9dB) - 9 (24dB)
            static constexpr byteArray<5> limit(uint8_t value) { return { CTRL, 0x04, 0x2C, ensureconstexprratitsU8(value, 4, 9), 0xFF}; };
            static constexpr byteArray<5> limitOff()           { return { CTRL, 0x04, 0x2C, 0x0F, 0xFF}; };

            //! \brief returns command packet for setting gain point
            static constexpr byteArray<5> point(State state) { return { CTRL, 0x05, 0x0C, state, 0xFF}; };

            //! \brief returns command packet for setting gain point position - value is in range 01 (0dB) - 09 (24dB)
            static constexpr byteArray<6> pointPosition(uint8_t value) { return { CTRL, 0x05, 0x4C, 0x00, ensureMaxU8(value, 0x09), 0xFF}; };
        };

        namespace Shutter
        {
            static constexpr byteArray<5> change(ChangeEnum change) { return { CTRL, 0x04, 0x0A, change, 0xFF}; };

            //! \brief returns command packet for setting shutter - value is in range 0x01 - 0x15
            static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x4A, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; };

            static constexpr byteArray<4> getValue()              { return { INQ, 0x04, 0x4A, 0xFF}; };
            static uint8_t valueFromReply(byteArray<7> reply) { return reversePrase(reply[4], reply[5]); };
        };

        // Max/min shutter, AE Speed, Exp Comp, Back Light, spot light, visibility enhancer, ir cut, low light basis brightness, nd filter
    };

    namespace Color
    {
        static constexpr byteArray<5> speed(uint8_t value) { return {CTRL, 0x04, 0x56, ensureconstexprratitsU8(value, 0x01, 0x59), 0xFF}; };

        namespace WhiteBalance
        {
            enum Mode : uint8_t {AUTO = 0, INDOOR = 1, OUTDOOR = 2, ONE_PUSH = 3, MANUAL = 5, OUTDOOR_AUTO = 6, SODIUM_LAMP_AUTO = 7, SODIUM_AUTO = 8 };

            static constexpr byteArray<5> setMode(Mode mode) { return {0x01, 0x04, 0x35, mode, 0xFF}; };
        };

        namespace RGain
        {
            static constexpr byteArray<5> change(ChangeEnum change) { return { CTRL, 0x04, 0x03, change, 0xFF}; };

            // Direct - 8x 01 04 43 00 00 0p 0p FF - pp: 00 (–128) - 80 (0) - FF (128)
        };

        namespace BGain
        {
            static constexpr byteArray<5> change(ChangeEnum change) { return { CTRL, 0x04, 0x04, change, 0xFF}; };

            // Direct - 8x 01 04 44 00 00 0p 0p FF - pp: 00 (–128) - 80 (0) - FF (128)
        };

        namespace Offset
        {
            static constexpr byteArray<7> change(ChangeEnum change) { return { CTRL, 0x7E, 0x01, 0x2E, 0x00, change, 0xFF}; };

            // Direct - 8x 01 7E 01 2E 01 0p FF - p: 0 (–7) - 7 (0) - E (+7)
        };

        // Chroma suppress, matrix, level, phase, R-G, R-B, ..., B-G
    };

    namespace Detail
    {
        namespace Level
        {
            static constexpr byteArray<5> change(ChangeEnum change) { return { CTRL, 0x04, 0x02, change, 0xFF}; };

            // Direct - 8x 01 04 42 00 00 0p 0p FF - pp: Aperture Gain 00 - 0F
        };

        // Mode, bandwith, crispening, h/v balance, b/w balance, limit, highlightide tail, superlow
    };

    namespace Gamma
    {
        enum Mode : uint8_t {STD = 0, STRAIGHT = 1, PATTERN = 2, MOVIE = 8, STILL = 9, CINE1 = 0xA, CINE2  = 0xB, CINE3 = 0xC, CINE4  = 0xE, ITU709  = 0xE};
        static constexpr byteArray<5> setMode(Mode mode) { return {0x01, 0x04, 0x5B, mode, 0xFF}; };

        // Pattern           - 8x 01 05 5B 0p 0p 0p FF          - ppp: 001 - 200
        // Offset            - 8x 01 04 1E 00 00 00 0p 0q 0q FF - p: Offset polarity 0 (+), 1 (–) and qq: Offset width 00 - 40

        static constexpr byteArray<7> level(uint8_t value) { return { CTRL, 0x7E, 0x01, 0x71, 00, ensureMaxU8(value, 0x0E), 0xFF}; };

        // Black gamma level - 8x 01 7E 01 72 0p 0p FF          - pp: 00 - 0E
        // Black gamma range - 8x 01 05 5C 0p FF                - p: Correction range 0 (Low), 1 (Mid), 2 (High)

        struct BlackLevel
        {
            //! \brief returns command packet for chaning gamma black level - value is in range 0x00 (–48) - 0x60 (48)
            static byteArray<7> direct(uint16_t value)
            {
                uint16_t limitedValue = ensureMaxU16(value, 0x60);
                return {CTRL, 0x7E, 0x04, 0x45, parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
            };
        };
    };

    // Picture profile mode   - 8x 01 7E 04 5F 0p FF p: - Picture profile setting (0=PP1, 1=PP2, 2=PP3, 3=PP4, 4=PP5, 5=PP6)
    // Flicker reduction mode - 8x 01 04 32 0p FF       - p:2=On, 3=Off

    //! \brief returns command packet for changing noise reduction - value is in range 01 (Weak) - 05 (Strong)
    static constexpr byteArray<5> flickerReduction(State state) { return {CTRL, 0x04, 0x32, state, 0xFF}; };

    //! \brief returns command packet for changing noise reduction - value is in range 01 (Weak) - 05 (Strong)
    static constexpr byteArray<5> noiseReduction(uint8_t value) { return {CTRL, 0x04, 0x53, ensureMaxU8(value, 05), 0xFF}; };
    static constexpr byteArray<5> vibrationCompensation(bool state) { return {CTRL, 0x04, 0x34, (uint8_t) (state ? 0x02 : 0x03), 0xFF}; };

    namespace Zoom
    {
        static byteArray<5> stop()         { return {CTRL, 0x04, 0x07, 0x00,  0xFF}; };
        static byteArray<5> teleStandard() { return {CTRL, 0x04, 0x07, 0x02,  0xFF}; };
        static byteArray<5> wideStandard() { return {CTRL, 0x04, 0x07, 0x03,  0xFF}; };

        //! \brief speed is in range 0 - 7 (from slowest to fastest)
        static byteArray<5> teleVariable(uint8_t speed) { return {CTRL, 0x04, 0x07, (uint8_t) (0x20|(ensureMaxU8(speed, 7U))),  0xFF}; };
        //! \brief speed is in range 0 - 7 (from slowest to fastest)
        static byteArray<5> wideVariable(uint8_t speed) { return {CTRL, 0x04, 0x07, (uint8_t) (0x30|(ensureMaxU8(speed, 7U))),  0xFF}; };

        //! \brief value is in range 0x0 - 0x4000 (from wide to tele)
        static byteArray<8> setValue(uint16_t value)
        {
            uint16_t limitedValue = ensureMaxU16(value, 0x4000);
            return {CTRL, 0x04, 0x47, parseParam(limitedValue, 3), parseParam(limitedValue, 2), parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
        };

        static constexpr byteArray<4> getValue()              { return { INQ, 0x04, 0x47, 0xFF}; };
        static uint8_t valueFromReply(byteArray<7> reply) { return reversePrase(reply[2], reply[3], reply[4], reply[5]); };
    };

    namespace Focus
    {
        enum FocusMode : uint8_t { AUTO=0x02, MANUAL=0x03, TOGGLE_AUTO=0x10 };
        static constexpr byteArray<5> autoFocus(FocusMode focus) { return {CTRL, 0x04, 0x38, focus, 0xFF}; };

        enum Distance : uint8_t { FAR=0x02, NEAR=0x03 };
        static constexpr byteArray<5> setDistance(Distance focus) { return {CTRL, 0x04, 0x38, focus, 0xFF}; };
        //! \brief returns command packet for setting distance with variable speed - speed is in range 0 - 7 (from slowest to fastest)
        static constexpr byteArray<5> setDistanceVarSpeed(Distance focus, uint8_t spped) { return {CTRL, 0x04, 0x38, (uint8_t) (focus << 4 & spped), 0xFF}; };

        static constexpr byteArray<6> infinity() { return { CTRL, 0x04, 0x18, 0x02, 0xFF}; };

        //! \brief  returns command packet for setting focus distance - value is in range F000 (Near) - 0000 (Far)
        static byteArray<8> setValue(uint16_t value)
        {
            uint16_t limitedValue = ensureMaxU16(value, 0xF000);
            return {CTRL, 0x04, 0x48, parseParam(limitedValue, 3), parseParam(limitedValue, 2), parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
        };

        static constexpr byteArray<4> getValue()              { return { INQ, 0x04, 0x48, 0xFF}; };
        static uint8_t valueFromReply(byteArray<7> reply) { return reversePrase(reply[2], reply[3], reply[4], reply[5]); };
    };

    namespace Hdmi
    {
        enum Format : uint8_t { _1920_1080_59_94 = 0x00, _1920_1080_29_97 = 0x02, /* TODO ... */ };
        enum Colorspace : uint8_t {YCBCR = 0, RGB = 1};

        static constexpr byteArray<7> setFormat(Format format)             { return {0x01, 0x7E, 0x01, 0x1E, parseParam(format, 1), parseParam(format, 0), 0xFF}; };
        static constexpr byteArray<7> setcolorSpace(Colorspace colorSpace) { return {0x01, 0x7E, 0x01, 0x03, 0x00, colorSpace, 0xFF}; };
    };
}

#endif // VISCACOMMANDS_H
