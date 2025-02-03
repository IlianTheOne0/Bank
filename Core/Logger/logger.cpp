#include "logger.h"

void Logger::log(string message, LoggerTypes loggerType, Colors color)
{
    if (_isEnabled)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (loggerType)
        {
        case LoggerTypes::Own: { SetConsoleTextAttribute(hConsole, color); } break;
        case LoggerTypes::Info: { SetConsoleTextAttribute(hConsole, LoggerTypes::Info); cout << "[ INFO ] "; } break;
        case LoggerTypes::InfoADD: { SetConsoleTextAttribute(hConsole, LoggerTypes::InfoADD); cout << "[ INFO ] "; } break;
        case LoggerTypes::Warning: { SetConsoleTextAttribute(hConsole, LoggerTypes::Warning); cout << "[ WARNING ] "; } break;
        case LoggerTypes::Error: { SetConsoleTextAttribute(hConsole, LoggerTypes::Error); cout << "[ ERROR ] "; } break;
        default: { SetConsoleTextAttribute(hConsole, _default); } break;
        }

        cout << message << endl;
        SetConsoleTextAttribute(hConsole, _default);
    }
}