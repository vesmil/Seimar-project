#ifndef VISCACOMMANDS_H
#define VISCACOMMANDS_H

#include <array>
#include <cstdint>

#include "global/logcategories.h"

// Duplicates could probably be avoided using builder pattern
//  ...but it would unnecessarily increase the complexity and would be slower

namespace {
    //! \brief returns value if value is less than max, else returns max (for uint8_t)
    constexpr uint8_t ensureMaxU8(uint8_t value, uint8_t max) { return value > max? max : value; }

    //! \brief returns value if within limits or return the limit
    constexpr uint8_t ensureConstrainsU8(uint8_t value, uint8_t min, uint8_t max) { return value > max ? max : (value < min ? min : value); }

    //! \brief returns value if value is less than max, else returns max (for uint16_t)
    constexpr uint16_t ensureMaxU16(uint16_t value, uint16_t max) { return value > max? max : value; }

    /*!
     * \brief used to split many bytes to half bytes - return least significant 4 bits from RShifting value by 4 * ordinal
     * \example parseParam(0x1234, 1) will return 2
     */
    constexpr uint8_t parseParam(uint16_t value, uint8_t reversedOrdinal) { return (value >> reversedOrdinal * 4) & 0x0F; }

    //! \brief Stopping condition for the template recursive function below
    template <typename TRet, typename T>
    constexpr TRet reverseParse(T param)
    {
        return param;
    }

    /*!
     * \brief Reverse of parseParam - combines multiple half-bytes into one number
     * \example reverseParse(0x0A, 0x04, 0x0B. 0x01) will return 0xA4B1
     */
    template <typename TRet = uint8_t, typename T, typename... Ts>
    constexpr TRet reverseParse(T firstParam, Ts ... params)
    {
        return (firstParam << 4 * sizeof...(params)) | reverseParse<TRet>(params...);
    }
}

/*!
 * \brief Namespace containing all necessary Visca commands with configurable parameters
 * \note Before the command is sent, it must be prepended with address of the camera
 */
namespace ViscaCommands
{
    template <std::size_t size>
    using byteArray = std::array<uint8_t, size>;

    enum CommandType : uint8_t { CTRL = 0x01, INQ = 0x09 };
    enum State       : uint8_t { ON = 0x02, OFF = 0x03 };

    //!  \brief Used to remap values from one range to another
    template <typename TNew, typename TOld>
    constexpr TNew mapToNewRange(TOld value, TOld oldMin, TOld oldMax, TNew newMin, TNew newMax)
    {
        return (value - oldMin) * (newMax - newMin) / (oldMax - oldMin) + newMin;
    }

    namespace Init
    {
        //! \brief returns command body for setting address - this needs to be broadcasted and address from reply needs to be noted
        [[maybe_unused]] static constexpr byteArray<3> addressSet() { return { 0x30, 0x01, 0xFF}; }
        //! \brief returns command body for clearing command buffer
        [[maybe_unused]] static constexpr byteArray<4> ifClear()    { return { CTRL, 0x00, 0x01, 0xFF}; }

        [[maybe_unused]] static constexpr byteArray<4> getVersionInfo() { return { INQ, 0x00, 0x02, 0xFF}; }
        [[maybe_unused]] static void printVersionInfo(byteArray<10> reply)
        {
            qCInfo(viscaLog()) << "Vendor ID:" << Qt::hex << (((uint16_t) reply[2] << 8) + reply[3]);
            qCInfo(viscaLog()) << "Model ID:" << Qt::hex << (((uint16_t) reply[4] << 8) + reply[5]);
            qCInfo(viscaLog()) << "ROM revision:" << Qt::hex << (((uint16_t) reply[6] << 8) + reply[7]);
            qCInfo(viscaLog()) << "Maximum socket #:" << Qt::hex << (reply[8]);
        }
    }

    namespace Power
    {
        [[maybe_unused]] static constexpr byteArray<5> setState(State state) { return {CTRL, 0x04, 0x00, state, 0xFF}; }

        [[maybe_unused]] static constexpr byteArray<4> getState()            { return {INQ, 0x04, 0x00, 0xFF}; }
        [[maybe_unused]] static constexpr State stateFromReply(byteArray<4> reply) { return (State) reply[2];}
    }

    namespace Exposure
    {    
        enum Mode : uint8_t {FULL_AUTO = 0x00, MANUAL = 0x03, SHUTTER_PRI = 0x0A, IRIS_PRI = 0x0B, GAIN_PRI = 0x0E };
        static const std::array ModeArray { std::pair<Mode, QString>{FULL_AUTO, QString("Full auto")},
                                                                                std::pair<Mode, QString>{MANUAL, QString("Manual")},
                                                                                std::pair<Mode, QString>{SHUTTER_PRI, QString("Shutter")},
                                                                                std::pair<Mode, QString>{IRIS_PRI, QString("Iris priority")},
                                                                                std::pair<Mode, QString>{GAIN_PRI, QString("Gain priority")}};

        [[maybe_unused]] static constexpr byteArray<5> setMode(Mode mode)  { return { CTRL, 0x04, 0x39, mode, 0xFF}; }
        [[maybe_unused]] static constexpr byteArray<4> getMode()           { return { INQ, 0x04, 0x39, 0xFF}; }
        [[maybe_unused]] static constexpr Mode modeFromReply(byteArray<4> reply) { return (Mode) reply[2];}

        namespace Iris
        {
            //! \brief returns command body for setting iris - value is in range 0x05 - 0x15
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) {
                uint8_t fixedValue = ensureConstrainsU8(value, 0x05, 0x15);
                return { CTRL, 0x04, 0x4B, 0x00, 0x00, parseParam(fixedValue, 1), parseParam(fixedValue, 0), 0xFF};
            }
            [[maybe_unused]] static constexpr byteArray<4> getValue()              { return { INQ, 0x04, 0x4B, 0xFF}; }
            [[maybe_unused]] static constexpr uint8_t valueFromReply(byteArray<7> reply) { return reverseParse(reply[4], reply[5]); }
        }

        namespace Gain
        {
            //! \brief returns command body for setting gain - value is in range 0x00 (–3dB) - 0x0C (33 dB)
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x4C, 0x00, 0x00, 0, ensureMaxU8(value, 0x0C), 0xFF}; }
            [[maybe_unused]] static constexpr byteArray<4> getValue()              { return { INQ, 0x04, 0x4C, 0xFF}; }
            [[maybe_unused]] static constexpr uint8_t valueFromReply(byteArray<7> reply) { return reverseParse(reply[4], reply[5]); }

            //! \brief returns command body for setting gain limit - value is in range 0x04 (9dB) - 0x09 (24dB)
            [[maybe_unused]] static constexpr byteArray<5> limit(uint8_t value) { return {CTRL, 0x04, 0x2C,
                                                                         ensureConstrainsU8(value, 4, 9), 0xFF}; }
            [[maybe_unused]] static constexpr byteArray<5> limitOff()           { return { CTRL, 0x04, 0x2C, 0x0F, 0xFF}; }

            //! \brief returns command body for setting gain point
            [[maybe_unused]] static constexpr byteArray<5> point(State state) { return { CTRL, 0x05, 0x0C, state, 0xFF}; }

            //! \brief returns command body for setting gain point position - value is in range 0x01 (0dB) - 0x09 (24dB)
            [[maybe_unused]] static constexpr byteArray<6> pointPosition(uint8_t value) { return { CTRL, 0x05, 0x4C, 0x00, ensureMaxU8(value, 0x09), 0xFF}; }
        }

        namespace Shutter
        {
            //! \brief returns command body for setting shutter - value is in range 0x01 - 0x15
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x4A, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; }
            [[maybe_unused]] static constexpr byteArray<4> getValue()              { return { INQ, 0x04, 0x4A, 0xFF}; }
            [[maybe_unused]] static constexpr uint8_t valueFromReply(byteArray<7> reply) { return reverseParse(reply[4], reply[5]); }
        }

        namespace Compensation
        {
            [[maybe_unused]] static constexpr byteArray<5> setState(State state) { return { CTRL, 0x04, 0x3E, state, 0xFF}; }

            //! \brief returns command body for setting exposure compensation - value is in range 0x00 - 0x0E
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value)
            {
                uint8_t fixedValue = ensureMaxU8(value, 0x0E);
                return { CTRL, 0x04, 0x4E, 0x00, 0x00, parseParam(fixedValue, 1), parseParam(fixedValue, 0), 0xFF};
            }
        }

        [[maybe_unused]] static constexpr byteArray<5> backLightCompensation(State state) { return { CTRL, 0x04, 0x33, state, 0xFF}; }

        [[maybe_unused]] static constexpr byteArray<5> visibilityEnhancer(State state) { return { CTRL, 0x04, 0x3D, (uint8_t) (state == ON ? 0x03 : 0x06), 0xFF}; }

        enum BrightnessEnum : uint8_t {VERY_DARK = 0x00, DARK = 0x01, STANDARD = 0x02, BRIGHT = 0x03};
        enum CompensationEnum : uint8_t {LOW = 0x00, MID = 0x01, HIGH = 0x02};

        /*!
         * \brief returns command body for setting brightness compensation
         * \param effectLevel : 0 (Dark) - 6 (Bright)
         * \param brightnessCompensation is defined by enum : 0 (Very dark), 1 (Dark),2 (Standard), 3 (Bright)
         * \param compensationLevel is defined by enum : 0 (Low), 1 (Mid), 2 (High)
         */
        [[maybe_unused]] static constexpr byteArray<12> setVisibilityEnhancer(uint8_t effectLevel, BrightnessEnum brightnessCompensation, CompensationEnum compensationLevel)
        { return { CTRL, 0x04, 0x2D, 0x00, ensureMaxU8(effectLevel, 0x6), brightnessCompensation, compensationLevel, 0x00, 0x00, 0x00, 0x00 ,0xFF}; }
    }

    namespace Color
    {
        [[maybe_unused]] static constexpr byteArray<5> blackAndWhite(State state) { return { CTRL, 0x04, 0x63, (uint8_t) (state == ON? 0x04 : 0x00), 0xFF}; }

        namespace WhiteBalance
        {
            static constexpr std::size_t ModeCount = 8;
            enum Mode : uint8_t {AUTO = 0, INDOOR = 1, OUTDOOR = 2, ONE_PUSH = 3, MANUAL = 5, OUTDOOR_AUTO = 6, SODIUM_LAMP_AUTO = 7, SODIUM_AUTO = 8 };
            static const std::array<std::pair<Mode, QString>,ModeCount> ModeArray { std::pair<Mode, QString>{AUTO, QString("Auto")},
                                                                                    std::pair<Mode, QString>{INDOOR, QString("Indoor")},
                                                                                    std::pair<Mode, QString>{OUTDOOR, QString("Outdoor")},
                                                                                    std::pair<Mode, QString>{ONE_PUSH, QString("One push")},
                                                                                    std::pair<Mode, QString>{MANUAL, QString("Manual")},
                                                                                    std::pair<Mode, QString>{OUTDOOR_AUTO, QString("Outdoor auto")},
                                                                                    std::pair<Mode, QString>{SODIUM_LAMP_AUTO, QString("Sodium lamp auto")},
                                                                                    std::pair<Mode, QString>{SODIUM_AUTO, QString("Sodium auto")}};

            [[maybe_unused]] static constexpr byteArray<5> setMode(Mode mode) { return {0x01, 0x04, 0x35, mode, 0xFF}; }
        }

        namespace RGain
        {        
            //! \brief returns command body for setting red gain - value is in range 0x00 (–128) - 0x80 (0) - 0xFF (128)
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x43, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; }
        }

        namespace BGain
        {
            //! \brief returns command body for setting blue gain - value is in range 0x00 (–128) - 0x80 (0) - 0xFF (128)
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x44, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; }
        }

        namespace Gain {
            [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x49, 0x00, 0x00, 0x00, ensureMaxU8(value, 0x0E), 0xFF}; }
        }
    }

    namespace Aperture
    {
        //! \brief returns command body for setting aperture gain - value is in range 0x00 - 0x0F
        [[maybe_unused]] static constexpr byteArray<8> setValue(uint8_t value) { return { CTRL, 0x04, 0x42, 0x00, 0x00, parseParam(value, 1), parseParam(value, 0), 0xFF}; }

        enum Mode : uint8_t { AUTO=0x00, MANUAL=0x01};
        //! \brief returns command body for setting aperture mode - value is defined by enum : 0 (Auto), 1 (Manual)
        [[maybe_unused]] static constexpr byteArray<7> setMode(Mode mode) { return { CTRL, 0x04, 0x05, 0x42, 0x01, mode, 0xFF}; }
    }

    namespace Gamma
    {
        enum Mode : uint8_t {STD = 0, STRAIGHT = 1, PATTERN = 2, MOVIE = 8, STILL = 9, CINE1 = 0xA, CINE2  = 0xB, CINE3 = 0xC, CINE4  = 0xE, ITU709  = 0xE};
        [[maybe_unused]] static constexpr byteArray<5> setMode(Mode mode) { return {0x01, 0x04, 0x5B, mode, 0xFF}; }

        enum Polarity : uint8_t {POSITIVE = 0, NEGATIVE = 1};

        //! \brief returns command body for setting gamma offset - polarity is defined by enum and value is in range 0x00 - 0x40
        [[maybe_unused]] static constexpr byteArray<10> setOffset(Polarity polarity, uint8_t width) {
            uint8_t fixedWidth = ensureMaxU8(width, 40);
            return { CTRL, 0x04, 0x1E, 0x00, 0x00, 0x00, polarity, parseParam(fixedWidth, 1), parseParam(fixedWidth, 0), 0xFF};
        }

        [[maybe_unused]] static constexpr byteArray<7> level(uint8_t value) { return { CTRL, 0x7E, 0x01, 0x71, 00, ensureMaxU8(value, 0x0E), 0xFF}; }

        struct BlackLevel
        {
            //! \brief returns command body for changing gamma black level - value is in range 0x00 (–48) - 0x60 (48)
            static byteArray<7> direct(uint16_t value)
            {
                uint16_t limitedValue = ensureMaxU16(value, 0x60);
                return {CTRL, 0x7E, 0x04, 0x45, parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
            };
        };
    }

    //! \brief returns command body for changing noise reduction - value is in range 0x01 (Weak) - 0x05 (Strong)
    [[maybe_unused]] static constexpr byteArray<5> flickerReduction(State state) { return { CTRL, 0x04, 0x32, state, 0xFF}; }

    //! \brief returns command body for changing noise reduction - value is in range 0x01 (Weak) - 0x05 (Strong)
    [[maybe_unused]] static constexpr byteArray<5> noiseReduction(uint8_t value) { return {CTRL, 0x04, 0x53, ensureMaxU8(value, 05), 0xFF}; }
    [[maybe_unused]] static constexpr byteArray<5> vibrationCompensation(State state) { return {CTRL, 0x04, 0x34, state, 0xFF}; }

    namespace Zoom
    {

        static const std::array<std::pair<float, QString>, 6> zoomArray { std::pair<float, QString>{1, QString("1x")}, std::pair<float, QString>{1.2, QString("1.2x")},
                                                                          std::pair<float, QString>{1.5, QString("1.5x")}, std::pair<float, QString>{2, QString("2x")},
                                                                          std::pair<float, QString>{5, QString("5x")}, std::pair<float, QString>{10, QString("10x")}};

        [[maybe_unused]] static constexpr byteArray<5> teleStandard() { return {CTRL, 0x04, 0x07, 0x02,  0xFF}; }
        [[maybe_unused]] static constexpr byteArray<5> wideStandard() { return {CTRL, 0x04, 0x07, 0x03,  0xFF}; }
        [[maybe_unused]] static constexpr byteArray<5> stop()         { return {CTRL, 0x04, 0x07, 0x00,  0xFF}; }

        //! \brief speed is in range 0x00 - 0x07 (from slowest to fastest)
        [[maybe_unused]] static constexpr byteArray<5> teleVariable(uint8_t speed) { return {CTRL, 0x04, 0x07, (uint8_t) (0x20|(ensureMaxU8(speed, 7U))),  0xFF}; }
        //! \brief speed is in range 0x00 - 0x07 (from slowest to fastest)
        [[maybe_unused]] static constexpr byteArray<5> wideVariable(uint8_t speed) { return {CTRL, 0x04, 0x07, (uint8_t) (0x30|(ensureMaxU8(speed, 7U))),  0xFF}; }

        //! \brief value is in range 0x00 - 0x4000 (from wide to tele)
        [[maybe_unused]] static constexpr byteArray<8> setValue(uint16_t value)
        {
            uint16_t fixedValue = ensureMaxU16(value, 0x4000);
            return {CTRL, 0x04, 0x47, parseParam(fixedValue, 3), parseParam(fixedValue, 2), parseParam(fixedValue, 1), parseParam(fixedValue, 0), 0xFF};
        }

        [[maybe_unused]] static constexpr byteArray<4> getValue() { return { INQ, 0x04, 0x47, 0xFF}; }
        [[maybe_unused]] static constexpr uint16_t valueFromReply(byteArray<7> reply) {
            return reverseParse<uint16_t>(reply[2], reply[3], reply[4], reply[5]); }
    }

    namespace Focus
    {
        enum FocusMode : uint8_t { AUTO=0x02, MANUAL=0x03, TOGGLE_AUTO=0x10 };
        [[maybe_unused]] static constexpr byteArray<5> setFocusMode(FocusMode focus) { return {CTRL, 0x04, 0x38, focus, 0xFF}; }

        enum Distance : uint8_t { FAR=0x02, NEAR=0x03 };
        [[maybe_unused]] static constexpr byteArray<5> setDistance(Distance focus) { return {CTRL, 0x04, 0x38, focus, 0xFF}; }
        //! \brief returns command body for setting distance with variable speed - speed is in range 0x00 - 0x07 (from slowest to fastest)
        [[maybe_unused]] static constexpr byteArray<5> setDistanceVarSpeed(Distance focus, uint8_t speed)
        { return {CTRL, 0x04, 0x38, (uint8_t) (focus << 4 & speed), 0xFF}; }

        [[maybe_unused]] static constexpr byteArray<5> infinity() { return { CTRL, 0x04, 0x18, 0x02, 0xFF}; }

        //! \brief  returns command body for setting focus distance - value is in range F000 (Near) - 0000 (Far)
        [[maybe_unused]] static constexpr byteArray<8> setValue(uint16_t value)
        {
            uint16_t limitedValue = ensureMaxU16(value, 0xF000);
            return {CTRL, 0x04, 0x48, parseParam(limitedValue, 3), parseParam(limitedValue, 2), parseParam(limitedValue, 1), parseParam(limitedValue, 0), 0xFF};
        }

        [[maybe_unused]] static constexpr byteArray<4> getValue() { return { INQ, 0x04, 0x48, 0xFF}; }
        [[maybe_unused]] static constexpr uint8_t valueFromReply(byteArray<7> reply) { return reverseParse<uint16_t>(reply[2], reply[3], reply[4], reply[5]); }
    }

    namespace Hdmi
    {
        static constexpr std::size_t FormatCount = 5;
        enum Format : uint8_t { _3840x2160_29_97HZ = 0x1D ,_3840x2160_25HZ = 0x1E ,  _1920x1080_59_94HZ = 0x13, _1920x1080_29_97HZ = 0x06, _1280x720_59_94HZ = 0x09};
        static const std::array<std::pair<ViscaCommands::Hdmi::Format, QString>, FormatCount> FormatArray {
            std::pair<ViscaCommands::Hdmi::Format, QString>{ViscaCommands::Hdmi::Format::_3840x2160_29_97HZ, QString("3840x2160\n 29.97HZ")},
            std::pair<ViscaCommands::Hdmi::Format, QString>{ViscaCommands::Hdmi::Format::_3840x2160_25HZ, QString("3840x2160\n 25HZ")},
            std::pair<ViscaCommands::Hdmi::Format, QString>{ViscaCommands::Hdmi::Format::_1920x1080_59_94HZ, QString("1920x1080\n 59.94HZ")},
            std::pair<ViscaCommands::Hdmi::Format, QString>{ViscaCommands::Hdmi::Format::_1920x1080_29_97HZ, QString("1920x1080\n 29.97HZ")},
            std::pair<ViscaCommands::Hdmi::Format, QString>{ViscaCommands::Hdmi::Format::_1280x720_59_94HZ, QString("1280x720\n 59.94HZ")},
        };

        static constexpr std::size_t ColorspaceCount = 2;
        enum Colorspace : uint8_t {YUV = 0, RGB = 1};
        static const std::array<std::pair<ViscaCommands::Hdmi::Colorspace, QString>, 2> ColorSpaceArray {
            std::pair<ViscaCommands::Hdmi::Colorspace, QString>{ViscaCommands::Hdmi::Colorspace::RGB, QString("RGB")},
            std::pair<ViscaCommands::Hdmi::Colorspace, QString>{ViscaCommands::Hdmi::Colorspace::YUV, QString("YUV")}};

        [[maybe_unused]] static constexpr byteArray<7> setFormat(Format format)             { return {0x01, 0x04, 0x24, 0x72, parseParam(format, 1), parseParam(format, 0), 0xFF}; }
        [[maybe_unused]] static constexpr byteArray<7> setColorspace(Colorspace colorSpace) { return {0x01, 0x04, 0x24, 0x60, 0x00, colorSpace, 0xFF}; }

        [[maybe_unused]] static constexpr byteArray<5> getColorspace() { return { INQ, 0x04, 0x24, 0x60, 0xFF}; }
        [[maybe_unused]] static constexpr uint8_t valueFromReply(byteArray<4> reply) { return reverseParse<uint16_t>(reply[2], reply[3]); }
    }

    [[maybe_unused]] static constexpr byteArray<5> horizontalFlip(State state) { return {CTRL, 0x04, 0x61, state, 0xFF}; }
    [[maybe_unused]] static constexpr byteArray<5> verticalFlip(State state)   { return {CTRL, 0x04, 0x66, state, 0xFF}; }
    [[maybe_unused]] static constexpr byteArray<5> freeze(State state) { return {CTRL, 0x04, 0x62, state, 0xFF}; }
}

#endif // VISCACOMMANDS_H
