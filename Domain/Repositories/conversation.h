#ifndef CONVERSATION_H
#define CONVERSATION_H

#include "../../Core/Libs/domainConfig.h"
#include "../../Domain/Entities/Account/statusEnum.h"

class Conversation
{
public:
    static string dateConversion(const tm& date);
    static tm dateConversion(const string& date);

    static string statusConversion(const Status& status);
    static Status statusConversion(const string& status);
};

#endif