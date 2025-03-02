#ifndef LOGGER_H
#define LOGGER_H

#include "../Libs/CoreConfig.h"
#include "colorsEnum.h"
#include "loggerTypesEnum.h"

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