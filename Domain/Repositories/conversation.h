#ifndef CONVERSATION_H
#define CONVERSATION_H

#include "../../Core/Libs/domainConfig.h"
#include "../../Domain/Entities/Account/accountStatusEnum.h"
#include "../../Domain/Entities/Transaction/transactionStatusEnum.h"

class Conversation
{
public:
    static string dateConversion(const tm& date);
    static tm dateConversion(const string& date);

    static string statusConversion(const AccountStatus& status);
    static AccountStatus statusConversion(const string& status);

    static string statusConversion(const TransactionStatus& status, bool indi);
    static TransactionStatus statusConversion(const string& status, bool indi);
};

#endif