#ifndef TEMP_ACCOUNT_H
#define TEMP_ACCOUNT_H

#include "../../../Core/Libs/domainConfig.h"
#include "accountStatusEnum.h"

struct Account
{
    size_t accountId;
    size_t clientId;
    float balance;
    string currency;
    tm openedDate;
    tm closedDate;
    AccountStatus status;
};

#endif