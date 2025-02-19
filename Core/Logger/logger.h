#ifndef LOGGER_H
#define LOGGER_H

#include "../Libs/CoreConfig.h"

enum Colors
{
    DefaultColor = 7,

    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Pink = 5,
    Yellow = 6,
    White = 7,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightPink = 13,
    LightYellow = 14,
    LightWhite = 15
};

enum LoggerTypes
{
    Info = 9,
    InfoADD = 11,
    Error = 12,
    Warning = 14,
    DefaultLogger = 7,
    Own
};

class Logger
{
protected:
    static bool _isEnabled;

    static const unsigned short _info = 9;
    static const unsigned short _error = 12;
    static const unsigned short _warning = 14;
    static const unsigned short _default = 7;
public:
    static void log(string message, LoggerTypes loggerType = LoggerTypes::DefaultLogger, Colors color = Colors::DefaultColor);
    static bool getState();
};

#endif